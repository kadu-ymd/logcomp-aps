import sys

from compiler import SymbolTable, Node, BinOp, IntVal, BoolVal, DirectionVal, ActionVal, \
                     CollectableVal, InteractableVal, StateVal, RelationalBoolVal, \
                     RelationalOperatorVal, NoOp, Identifier, MovementBlock, InteractBlock, \
                     AssignmentBlock, SequenceBlock, SequenceCall, ConditionalBlock, \
                     CollectableCondition, ObjectCondition, LoopBlock, CollectCommand, RootProgramNode


class EscapeRoomVM:
    def __init__(self, output_stream=sys.stdout):
        self.player_position = (0, 0)

        self.inventory = {}

        self.escaped = False

        self.room_objects = {
            "locker_up": {"type": "locker", "state": "locked", "content": "key"},
            "exit_door_right": {"type": "exit_door", "state": "locked", "requires": "key"},
            "desk_down": {"type": "desk", "state": "unlocked", "content": "key"}
        }

        self.room_map = {
            (0,0): {"up": "locker_up", "right": "exit_door_right", "down": "desk_down"}
        }

        self.output_stream = output_stream
        self._print("--- Welcome to the Escape Room VM! ---")
        self.display_room_state()

    def _print(self, message):
        print(message, file=self.output_stream)

    def display_room_state(self):
        self._print(f"\n[VM State] Player Position: {self.player_position}")
        self._print("[VM State] Room Objects:")

        for obj_name, obj_data in self.room_objects.items():
            content_display = obj_data.get('content', 'N/A')

            if content_display is None:
                content_display = 'Empty'
            
            if obj_data.get('type') == 'exit_door' and 'requires' in obj_data:
                 self._print(f"  - {obj_name.replace('_', ' ').title()}: State - {obj_data['state']}, Requires - {obj_data['requires']}")

            else:
                self._print(f"  - {obj_name.replace('_', ' ').title()}: State - {obj_data['state']}, Content - {content_display}")
                
        self._print(f"[VM State] Inventory: {self.inventory}")

    def move_player(self, direction, units):
        self._print(f"[VM Action] Moving {direction} for {units} units.")

        if direction == "up":
            self.player_position = (self.player_position[0], self.player_position[1] + units)

        elif direction == "down":
            self.player_position = (self.player_position[0], self.player_position[1] - units)

        elif direction == "left":
            self.player_position = (self.player_position[0] - units, self.player_position[1])

        elif direction == "right":
            self.player_position = (self.player_position[0] + units, self.player_position[1])

        self._print(f"[VM Action] Player moved to {self.player_position}")
        self.display_room_state()

    def get_object_at_direction(self, direction):
        return self.room_map.get(self.player_position, {}).get(direction)

    def open_object(self, direction):
        object_name = self.get_object_at_direction(direction)

        if object_name and object_name in self.room_objects:
            obj = self.room_objects[object_name]
            self._print(f"[VM Action] Attempting to open {object_name}.")

            if obj["type"] == "exit_door":
                if obj["state"] == "locked":
                    if "key" in self.inventory and self.inventory["key"] > 0:
                        obj["state"] = "unlocked"
                        self.inventory["key"] -= 1
                        self.escaped = True
                        self._print(f"[VM Result] The {object_name} is now unlocked! (Key used)")
                        self.display_room_state()

                        return True
                    else:
                        self._print(f"[VM Result] The {object_name} is locked. You need a key.")
                        return False
                    
                elif obj["state"] == "unlocked":
                    self._print(f"[VM Result] The {object_name} is already unlocked. You escaped!")
                    self.escaped = True
                    sys.exit(0) 

            elif obj["state"] == "locked":
                self._print(f"[VM Result] The {object_name} is locked and cannot be opened directly.")
                return False
            
            else:
                self._print(f"[VM Result] The {object_name} is open.")
                self.display_room_state()
                return True
            
        self._print(f"[VM Result] No interactable object found in direction {direction} to open.")
        self.display_room_state()
        return False

    def collect_item_from_room(self, item_name, direction):
        object_name = self.get_object_at_direction(direction)

        if object_name and object_name in self.room_objects:
            obj = self.room_objects[object_name]

            self._print(f"[VM Action] Attempting to collect '{item_name}' from {object_name}.")

            if obj["content"] == item_name:
                self.inventory[item_name] = self.inventory.get(item_name, 0) + 1
                obj["content"] = None
                self._print(f"[VM Result] Collected '{item_name}' from {object_name}. Inventory: {self.inventory}")
                self.display_room_state()
                return True
            
            else:
                self._print(f"[VM Result] '{item_name}' not found in {object_name}.")
                return False
            
        self._print(f"[VM Result] No object found in direction {direction} to collect '{item_name}' from.")
        return False

    def check_object_state(self, direction, relational_bool, target_state_or_type):
        object_name = self.get_object_at_direction(direction)
        if object_name and object_name in self.room_objects:
            obj = self.room_objects[object_name]
            
            is_match = False
            if target_state_or_type in ["locked", "unlocked"]:
                is_match = (obj["state"] == target_state_or_type)

            elif target_state_or_type in ["locker", "closet", "desk", "exit_door"]:
                is_match = (obj["type"] == target_state_or_type)
            
            result = is_match if relational_bool == "is" else (not is_match)

            self._print(f"[VM Condition Check] Object at '{direction}' is '{obj['type']}' and '{obj['state']}'. Condition '{target_state_or_type}' {relational_bool}: {result}")
            return result
        
        self._print(f"[VM Condition Check] No object found at '{direction}' to check state/type. Defaulting to False.")
        return False

    def execute_ast(self, ast_root_node: RootProgramNode):
        self._print("\n--- Starting AST Execution on VM ---")
        execution_st = SymbolTable()
        
        for child_node in ast_root_node.children:
            self._evaluate_node(child_node, execution_st)
        self._print("--- AST Execution Finished ---")


    def _evaluate_node(self, node: Node, st: SymbolTable):
        if isinstance(node, RootProgramNode):
            for child in node.children:
                self._evaluate_node(child, st)

        elif isinstance(node, MovementBlock):
            direction = node.children[0].evaluate(st)[1]
            value = node.children[1].evaluate(st)[1]
            self.move_player(direction, value)

        elif isinstance(node, InteractBlock):
            action = node.children[0].evaluate(st)[1]
            direction = node.children[1].evaluate(st)[1]

            if action == "open":
                return ("bool", self.open_object(direction), False)
            
            elif action == "collect":
                return ("bool", self.collect_item_from_room(node.children[0].evaluate(st)[1], direction), False)

            return ("bool", False, False)
        
        elif isinstance(node, AssignmentBlock):
            var_iden_node = node.children[0]
            interact_node = node.children[1]

            var_name = var_iden_node.value
            interaction_result_tuple = self._evaluate_node(interact_node, st) 
            
            try:
                declared_type_info = st.get(var_name)
                if interaction_result_tuple[0] != declared_type_info[0]:
                    raise Exception(f"Erro de tipo em VM: Atribuição para '{var_name}' esperava '{declared_type_info[0]}', mas recebeu '{interaction_result_tuple[0]}'.")
                
                st.set(var_name, interaction_result_tuple)

            except Exception:
                st.create(var_name, interaction_result_tuple)

        elif isinstance(node, SequenceBlock):
            sequence_name = node.value
            st.create(sequence_name, ("sequence", node, True))
            self._print(f"[VM] Sequence '{sequence_name}' defined.")

        elif isinstance(node, SequenceCall):
            sequence_declaration = st.get(node.value)

            if sequence_declaration[2] and sequence_declaration[0] == "sequence":
                st_chained = SymbolTable(st) 
                self._print(f"[VM] Calling sequence '{node.value}'.")

                for statement_node in sequence_declaration[1].children:
                    self._evaluate_node(statement_node, st_chained)

            else:
                raise Exception(f"'{node.value}' não é uma sequência definida na VM.")

        elif isinstance(node, ConditionalBlock):
            condition_eval_tuple = self._evaluate_node(node.children[0], st)

            if condition_eval_tuple[0] != "bool":
                raise Exception("Erro de tipo em VM: IF_CONDITION deve retornar um booleano.")
            
            if condition_eval_tuple[1]:
                st_chained = SymbolTable(st)

                for statement_node in node.children[1]:
                    self._evaluate_node(statement_node, st_chained)
            else:
                st_chained = SymbolTable(st)
                for statement_node in node.children[2]:
                    self._evaluate_node(statement_node, st_chained)
        
        elif isinstance(node, CollectableCondition):
            identifier_value_tuple = node.children[0].evaluate(st)
            identifier_value = identifier_value_tuple[1]
            operator = node.children[1].evaluate(st)[1]
            value_eval_tuple = node.children[2].evaluate(st)
            value = value_eval_tuple[1]
            
            if st.get(identifier_value)[0] != "int" or value_eval_tuple[0] != "int":
                raise Exception(f"Erro de tipo em VM: Condição com '{operator}' requer inteiros. Recebido {identifier_value_tuple[0]} e {value_eval_tuple[0]}.")

            if operator == "==": 
                return ("bool", st.get(identifier_value)[1] == value, False)
            
            if operator == ">": 
                return ("bool", st.get(identifier_value)[1] > value, False)
            
            if operator == "<":
                return ("bool", st.get(identifier_value)[1] < value, False)

            if operator == ">=":
                return ("bool", st.get(identifier_value)[1] >= value, False)

            if operator == "<=": 
                return ("bool", st.get(identifier_value)[1] <= value, False)

            if operator == "!=": 
                return ("bool", st.get(identifier_value)[1] != value, False)

        elif isinstance(node, ObjectCondition):
            direction = node.children[0].evaluate(st)[1]
            relational_bool = node.children[1].evaluate(st)[1]
            object_target = node.children[2].evaluate(st)[1]
            
            return ("bool", self.check_object_state(direction, relational_bool, object_target), False)

        elif isinstance(node, LoopBlock):
            condition_node = node.children[0]
            
            while self._evaluate_node(condition_node, st)[1]:
                st_chained = SymbolTable(st) 

                for statement_node in node.children[1]:
                    self._evaluate_node(statement_node, st_chained)
        
        elif isinstance(node, CollectCommand):
            collectable_name = node.children[0].evaluate(st)[1]
            direction = node.children[1].evaluate(st)[1]
            
            item_collected = self.collect_item_from_room(collectable_name, direction)

            if item_collected:
                try:
                    current_count_tuple = st.get(collectable_name)

                    if current_count_tuple[0] == "int":
                        st.set(collectable_name, ("int", current_count_tuple[1] + 1, False))
                        self._print(f"[VM] {collectable_name} now is: {st.get(collectable_name)[1]} in player's local inventory (SymbolTable).")

                    else:
                        raise Exception(f"Erro em VM: '{collectable_name}' não é um tipo numérico para coletar.")
                    
                except Exception:
                    st.create(collectable_name, ("int", 1, False))
                    self._print(f"[VM] First '{collectable_name}' collected! Value set to 1 in player's local inventory (SymbolTable).")

            else:
                self._print(f"[VM] Failed to collect '{collectable_name}'.")

        elif isinstance(node, (IntVal, BoolVal, DirectionVal, ActionVal, CollectableVal, InteractableVal, StateVal, RelationalBoolVal, RelationalOperatorVal)):
            return node.evaluate(st)

        elif isinstance(node, Identifier):
            return node.evaluate(st)

        elif isinstance(node, BinOp):
            return node.evaluate(st)

        elif isinstance(node, NoOp): # Para garantir que NoOp não cause erro
            pass
        
        else:
            raise NotImplementedError(f"Nó não implementado na VM: {type(node)}")