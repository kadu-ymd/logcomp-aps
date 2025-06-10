import sys
import re


VAR_PATTERN = "[a-zA-Z]([a-zA-Z]|_|[0-9])*"

RESERVED_WORDS = ["enter", "program", "end", "move", "interact", "define", "sequence", "conditional", "loop", "while", "up", "right", "down", "left", "locker", "closet", "desk", "exit_door", "locked", "unlocked", "is", "is_not", "object", "else", "if", "true", "false", "collect"]


class SymbolTable:
    def __init__(self, parent=None):
        self.table = dict()
        self.parent = parent

    def create(self, key: str, value):
        if key not in self.table:
            self.table[key] = value
            
        else:
            raise Exception(f"Variável '{key}' já declarada.")

    def get(self, key):
        if key in self.table:
            return self.table[key]
        
        elif self.parent is not None:
            return self.parent.get(key)
        
        else:
            raise Exception(f"Variável '{key}' não definida.")

    def set(self, key, value):
        if key in self.table:
            self.table[key] = value
        elif self.parent is not None:
            self.parent.set(key, value)
        else:
            raise Exception(f"Variável '{key}' não declarada.")


class Token:
    def __init__(self, type: str, value):
        self.type = type
        self.value = value


class PrePro:
    @staticmethod
    def filter(filename):
        with open(filename, "r", encoding="utf-8") as f:
            lines = f.readlines()

        aux = [re.sub("//.*", "", line) for line in lines]
        aux1 = [re.sub(r"\t+", "", line).strip(" ") for line in aux]

        return "".join(aux1)


class Tokenizer:
    def __init__(self, source: str, position: int, next: Token):
        self.source = source
        self.position = position
        self.next = next

    def select_next(self):
        value = []
        
        if self.position != len(self.source):
            while self.position < len(self.source) and self.source[self.position] == " ":
                self.position += 1

            if self.position == len(self.source):
                self.next = Token("EOF", None)
                return

            temp_pos = self.position
            while temp_pos < len(self.source) and \
                    (self.source[temp_pos].isdigit() or self.source[temp_pos].isalpha() or self.source[temp_pos] == "_"):
                value.append(self.source[temp_pos])
                temp_pos += 1

            self.position = temp_pos

            val = "".join(value)

            if len(val):
                if re.match(VAR_PATTERN, val, flags=0):
                    if val in RESERVED_WORDS:
                        if val == "true":
                            self.next = Token("bool", True)
                        elif val == "false":
                            self.next = Token("bool", False)
                        elif val in ["up", "right", "down", "left"]:
                            self.next = Token("direction", val)
                        elif val in ["key", "coins", "card"]:
                            self.next = Token("collectable", val)
                        elif val in ["locker", "closet", "desk", "exit_door"]:
                            self.next = Token("interactable", val)
                        elif val in ["locked", "unlocked"]:
                            self.next = Token("state", val)
                        elif val in ["is", "is_not"]:
                            self.next = Token("relational_bool", val)
                        else:
                            self.next = Token(f"{val}", None)
                    else:
                        self.next = Token("iden", val)
                elif val.isdigit():
                    self.next = Token("int", int(val))
                else:
                    raise Exception(f"Token inválido: {val}")
            else:
                if self.position >= len(self.source):
                    self.next = Token("EOF", None)
                    return
                
                char = self.source[self.position]
                next_char = self.source[self.position+1] if self.position + 1 < len(self.source) else ''

                if char == "=":
                    if next_char == "=":
                        self.next = Token("relational_operator", "==")
                        self.position += 1
                    else:
                        self.next = Token("assignment", "=")
                elif char == ">":
                    if next_char == "=":
                        self.next = Token("relational_operator", ">=")
                        self.position += 1
                    else:
                        self.next = Token("relational_operator", ">")
                elif char == "<":
                    if next_char == "=":
                        self.next = Token("relational_operator", "<=")
                        self.position += 1
                    else:
                        self.next = Token("relational_operator", "<")
                elif char == "!":
                    if next_char == "=":
                        self.next = Token("relational_operator", "!=")
                        self.position += 1
                    else:
                        raise Exception("Operador de negação '!' não esperado neste contexto.")
                
                elif char == ":":
                    self.next = Token("colon", ":")
                elif char == "\n":
                    self.next = Token("line_break", None)
                elif char == "{":
                    self.next = Token("open_brack", "{")
                elif char == "}":
                    self.next = Token("close_brack", "}")
                
                elif char == "(":
                    self.next = Token("open_par", "(")
                elif char == ")":
                    self.next = Token("close_par", ")")
                
                else:
                    raise Exception(f"Caracter inválido: '{char}' na posição {self.position}")
                self.position += 1
        else:
            self.next = Token("EOF", None)


class Node:
    def __init__(self, value, children: list):
        self.value = value
        self.children = children

    def evaluate(self, st: SymbolTable):
        raise NotImplementedError


class BinOp(Node):
    def evaluate(self, st):
        child_0, child_1 = self.children

        child_tuple_0 = child_0.evaluate(st)
        child_tuple_1 = child_1.evaluate(st)

        if child_tuple_0[0] != "int" or child_tuple_1[0] != "int":
             raise Exception(f"Erro de tipo: Condições com operadores relacionais (como {self.value}) devem comparar inteiros. Recebido {child_tuple_0[0]} e {child_tuple_1[0]}.")

        if self.value == "==": return ("bool", child_tuple_0[1] == child_tuple_1[1], False)

        if self.value == ">": return ("bool", child_tuple_0[1] > child_tuple_1[1], False)

        if self.value == "<": return ("bool", child_tuple_0[1] < child_tuple_1[1], False)

        if self.value == ">=": return ("bool", child_tuple_0[1] >= child_tuple_1[1], False)

        if self.value == "<=": return ("bool", child_tuple_0[1] <= child_tuple_1[1], False)

        if self.value == "!=": return ("bool", child_tuple_0[1] != child_tuple_1[1], False)
        
        raise Exception(f"Operador binário não suportado: {self.value}")


class IntVal(Node):
    def evaluate(self, st):
        return ("int", self.value, False)


class BoolVal(Node):
    def evaluate(self, st):
        return ("bool", self.value, False)


class NoOp(Node):
    def evaluate(self, st):
        pass


class Identifier(Node):
    def evaluate(self, st):
        try:
            return st.get(self.value)
        except Exception as e:
            raise Exception(f"Erro: {e}")


class MovementBlock(Node):
    def evaluate(self, st):
        direction = self.children[0].value
        value = self.children[1].evaluate(st)[1]

        print(f"Moving {direction} for {value} units.")

        return None


class InteractBlock(Node):
    def evaluate(self, st):
        action = self.children[0].value
        direction = self.children[1].value
        print(f"Interaction to {action} on direction {direction}.")
        
        if action == "open":
            return ("bool", True, False)
        
        elif action == "collect":
            return ("bool", True, False)
        
        return ("bool", False, False)


class AssignmentBlock(Node):
    def evaluate(self, st):
        var_iden_node = self.children[0]
        interact_node = self.children[1]

        var_name = var_iden_node.value
        interaction_result = interact_node.evaluate(st) 
        
        try:
            declared_type_info = st.get(var_name)

            if interaction_result[0] != declared_type_info[0]:
                raise Exception(f"Erro de tipo: Atribuição para '{var_name}' esperava '{declared_type_info[0]}', mas recebeu '{interaction_result[0]}'.")
            
            st.set(var_name, interaction_result)

        except Exception:
            st.create(var_name, interaction_result)
        
        return None


class SequenceBlock(Node):
    def evaluate(self, st):
        sequence_name = self.value

        st.create(sequence_name, ("sequence", self, True))

        return None


class SequenceCall(Node):
    def evaluate(self, st):
        sequence_declaration = st.get(self.value)

        if sequence_declaration[2] and sequence_declaration[0] == "sequence":
            st_chained = SymbolTable(st)

            for statement_node in sequence_declaration[1].children:
                statement_node.evaluate(st_chained)

            return None
        
        else:
            raise Exception(f"'{self.value}' não é uma sequência definida.")


class ConditionalBlock(Node):
    def evaluate(self, st):
        condition_eval = self.children[0].evaluate(st)
        
        if condition_eval[0] != "bool":
            raise Exception("Erro de tipo: IF_CONDITION deve retornar um booleano.")
        
        if condition_eval[1]:
            st_chained = SymbolTable(st)

            for statement_node in self.children[1]:
                statement_node.evaluate(st_chained)

        else:
            st_chained = SymbolTable(st)

            for statement_node in self.children[2]:
                statement_node.evaluate(st_chained)

        return None


class CollectableCondition(Node):
    def evaluate(self, st):
        identifier_node = self.children[0]
        operator = self.children[1].value
        value_node = self.children[2]

        identifier_value_tuple = identifier_node.evaluate(st)
        identifier_value = identifier_value_tuple[1]

        value_eval_tuple = value_node.evaluate(st)
        value = value_eval_tuple[1]

        if identifier_value_tuple[0] != "int" or value_eval_tuple[0] != "int":
            raise Exception(f"Erro de tipo: Condição com '{operator}' requer inteiros. Recebido {identifier_value_tuple[0]} e {value_eval_tuple[0]}.")

        if operator == "==": return ("bool", identifier_value == value, False)

        if operator == ">": return ("bool", identifier_value > value, False)

        if operator == "<": return ("bool", identifier_value < value, False)

        if operator == ">=": return ("bool", identifier_value >= value, False)

        if operator == "<=": return ("bool", identifier_value <= value, False)


        if operator == "!=": return ("bool", identifier_value != value, False)

        return ("bool", False, False)


class ObjectCondition(Node):
    def evaluate(self, st):
        direction = self.children[0].value
        relational_bool = self.children[1].value
        object_target = self.children[2].value

        print(f"Verifying if object at '{direction}' '{relational_bool}' '{object_target}'.")
        
        simulated_result = True
        
        if relational_bool == "is":
            return ("bool", simulated_result, False)
        elif relational_bool == "is_not":
            return ("bool", not simulated_result, False)
        return ("bool", False, False)


class LoopBlock(Node):
    def evaluate(self, st):
        condition_node = self.children[0]
        
        condition_eval_result = condition_node.evaluate(st)

        if condition_eval_result[0] != "bool":
            raise Exception("Erro de tipo: LOOP_CONDITION deve retornar um booleano.")

        while condition_node.evaluate(st)[1]:
            st_chained = SymbolTable(st)

            for statement_node in self.children[1]:
                statement_node.evaluate(st_chained)

        return None


class CollectCommand(Node):
    def evaluate(self, st):
        collectable = self.children[0].value
        direction = self.children[1].value
        print(f"Collecting '{collectable}' in direction '{direction}'.")
        
        item_name = collectable

        try:
            current_count_tuple = st.get(item_name)

            if current_count_tuple[0] == "int":
                st.set(item_name, ("int", current_count_tuple[1] + 1, False))
                print(f"{item_name} now is: {st.get(item_name)[1]}")

            else:
                raise Exception(f"Erro: '{item_name}' não é um tipo numérico para coletar.")
            
        except Exception:
            st.create(item_name, ("int", 1, False))
            print(f"First '{item_name}' collected!")
            
        return None


class RootProgramNode(Node):
    def evaluate(self, st: SymbolTable):
        for child in self.children:
            child.evaluate(st)


class Parser:
    tokenizer: Tokenizer

    @staticmethod
    def parse_factor() -> Node:
        node = NoOp(None, [])

        if Parser.tokenizer.next.type == "int":
            node = IntVal(Parser.tokenizer.next.value, [])

            Parser.tokenizer.select_next()

        elif Parser.tokenizer.next.type == "bool":
            node = BoolVal(Parser.tokenizer.next.value, [])

            Parser.tokenizer.select_next()
        
        elif Parser.tokenizer.next.type == "iden":
            node = Identifier(Parser.tokenizer.next.value, [])

            Parser.tokenizer.select_next()
        
        elif Parser.tokenizer.next.type == "open_par":
            Parser.tokenizer.select_next()

            node = Parser.parse_if_condition()

            if Parser.tokenizer.next.type != "close_par":
                raise Exception("Erro de sintaxe: parênteses não fechados.")
            
            Parser.tokenizer.select_next()

        else:
            raise Exception(f"Erro de sintaxe: token inválido em fator: {Parser.tokenizer.next.type} ('{Parser.tokenizer.next.value}')")

        return node

    @staticmethod
    def parse_statement() -> Node:
        node = NoOp(None, [])

        if Parser.tokenizer.next.type == "iden":
            identifier_node = Identifier(Parser.tokenizer.next.value, [])

            Parser.tokenizer.select_next()

            if Parser.tokenizer.next.type == "assignment":
                Parser.tokenizer.select_next()

                if Parser.tokenizer.next.type == "interact":
                    node = AssignmentBlock(None, [identifier_node, Parser.parse_interact_block()])

                else:
                    raise Exception(f"Erro de sintaxe: Atribuição inesperada. Somente 'IDENTIFIER = INTERACT_BLOCK' é permitido. Encontrado '{Parser.tokenizer.next.type}'.")
            
            elif Parser.tokenizer.next.type == "line_break":
                 node = SequenceCall(identifier_node.value, [])

            else:
                 raise Exception(f"Erro de sintaxe: Uso inesperado de identificador. Esperado '=', ou quebra de linha para chamada de sequência. Encontrado '{Parser.tokenizer.next.type}'.")

        elif Parser.tokenizer.next.type == "move":
            node = Parser.parse_movement_block()

        elif Parser.tokenizer.next.type == "interact":
            node = Parser.parse_interact_block()

        elif Parser.tokenizer.next.type == "define":
            node = Parser.parse_sequence_block()

        elif Parser.tokenizer.next.type == "if":
            node = Parser.parse_conditional_block()

        elif Parser.tokenizer.next.type == "while":
            node = Parser.parse_loop_block()

        elif Parser.tokenizer.next.type == "collect":
            node = Parser.parse_collect_command()
        
        else:
            node = NoOp(None, [])


        if isinstance(node, NoOp) and Parser.tokenizer.next.type != "line_break":
            raise Exception(f"Erro de sintaxe: Token inesperado '{Parser.tokenizer.next.type}' ('{Parser.tokenizer.next.value}').")
        
        elif not isinstance(node, NoOp) and Parser.tokenizer.next.type != "line_break":
            raise Exception(f"Erro de sintaxe: Statement deve terminar com uma quebra de linha. Encontrado '{Parser.tokenizer.next.type}' ('{Parser.tokenizer.next.value}') em vez disso.")
        
        if Parser.tokenizer.next.type == "line_break":
            Parser.tokenizer.select_next()

        return node

    @staticmethod
    def parse_program() -> Node:
        program_statements = []

        if Parser.tokenizer.next.type != "enter":
            raise Exception("Erro de sintaxe: Programa deve começar com 'enter'")
        
        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "line_break":
            raise Exception("Erro de sintaxe: Esperado quebra de linha após 'enter'")
        
        Parser.tokenizer.select_next()

        while Parser.tokenizer.next.type not in ["program", "EOF"]:
            program_statements.append(Parser.parse_statement())

        if Parser.tokenizer.next.type != "program":
            raise Exception("Erro de sintaxe: Esperado palavra-chave 'program'")
        
        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "end":
            raise Exception("Erro de sintaxe: Esperado palavra-chave 'end'")
        
        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type == "line_break":
            Parser.tokenizer.select_next()
        
        if Parser.tokenizer.next.type != "EOF":
            raise Exception(f"Erro de sintaxe: Esperado EOF, mas encontrado '{Parser.tokenizer.next.type}' ('{Parser.tokenizer.next.value}')")

        return RootProgramNode(None, program_statements)
    
    @staticmethod
    def parse_movement_block() -> MovementBlock:
        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "direction":
            raise Exception("Erro de sintaxe: Esperado DIREÇÃO após 'move'")
        
        direction_token = Parser.tokenizer.next

        Parser.tokenizer.select_next()

        value_node = Parser.parse_factor()

        return MovementBlock(None, [direction_token, value_node])

    @staticmethod
    def parse_interact_block() -> InteractBlock:
        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.value not in ["open", "collect"]:
            raise Exception("Erro de sintaxe: Esperado 'open' ou 'collect' após 'interact'")
        
        action_token = Parser.tokenizer.next

        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "direction":
            raise Exception("Erro de sintaxe: Esperado DIREÇÃO após ação de 'interact'")
        
        direction_token = Parser.tokenizer.next

        Parser.tokenizer.select_next()

        return InteractBlock(None, [action_token, direction_token])

    @staticmethod
    def parse_sequence_block() -> SequenceBlock:
        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "sequence":
            raise Exception("Erro de sintaxe: Esperado 'sequence' após 'define'")
        
        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "iden":
            raise Exception("Erro de sintaxe: Esperado IDENTIFICADOR após 'sequence'")
        
        sequence_name = Parser.tokenizer.next.value

        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "colon":
            raise Exception("Erro de sintaxe: Esperado ':' após identificador da sequência")
        
        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "line_break":
            raise Exception("Erro de sintaxe: Esperado nova linha após ':' na definição de sequência")
        
        Parser.tokenizer.select_next()

        statements = []
        while Parser.tokenizer.next.type != "sequence":
            statements.append(Parser.parse_statement())
        
        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "end":
            raise Exception("Erro de sintaxe: Esperado 'end' após 'sequence' tag")
        
        Parser.tokenizer.select_next()

        return SequenceBlock(sequence_name, statements)
    
    @staticmethod
    def parse_conditional_block() -> ConditionalBlock:
        Parser.tokenizer.select_next()
        
        condition_node = Parser.parse_if_condition()
        
        if Parser.tokenizer.next.type != "colon":
            raise Exception("Erro de sintaxe: Esperado ':' após IF_CONDITION")
        
        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "line_break":
            raise Exception("Erro de sintaxe: Esperado nova linha após ':' no bloco condicional")
        
        Parser.tokenizer.select_next()

        if_statements = []
        while Parser.tokenizer.next.type != "else":
            if_statements.append(Parser.parse_statement())
        
        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "colon":
            raise Exception("Erro de sintaxe: Esperado ':' após 'else'")
        
        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "line_break":
            raise Exception("Erro de sintaxe: Esperado nova linha após ':' no bloco 'else'")
        
        Parser.tokenizer.select_next()

        else_statements = []
        while Parser.tokenizer.next.type != "conditional":
            else_statements.append(Parser.parse_statement())

        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "end":
            raise Exception("Erro de sintaxe: Esperado 'end' após 'conditional' tag")
        
        Parser.tokenizer.select_next()

        return ConditionalBlock(None, [condition_node, if_statements, else_statements])

    @staticmethod
    def parse_if_condition() -> Node:
        if Parser.tokenizer.next.type == "object":
            return Parser.parse_object_condition()
        
        current_pos = Parser.tokenizer.position
        current_next = Parser.tokenizer.next
        
        temp_tokenizer = Tokenizer(Parser.tokenizer.source, current_pos, current_next)
        temp_tokenizer.select_next()

        if temp_tokenizer.next.type == "relational_operator":
            return Parser.parse_collectable_condition()
        
        return Parser.parse_factor()

    @staticmethod
    def parse_collectable_condition() -> CollectableCondition:
        if Parser.tokenizer.next.type != "iden":
            raise Exception("Erro de sintaxe: Esperado IDENTIFICADOR para COLLECTABLE_CONDITION")
        
        identifier_node = Identifier(Parser.tokenizer.next.value, [])

        Parser.tokenizer.select_next()
        
        if Parser.tokenizer.next.type != "relational_operator":
            raise Exception("Erro de sintaxe: Esperado OPERADOR_RELACIONAL")
        
        operator_token = Parser.tokenizer.next

        Parser.tokenizer.select_next()

        value_node = Parser.parse_factor()

        return CollectableCondition(None, [identifier_node, operator_token, value_node])

    @staticmethod
    def parse_object_condition() -> ObjectCondition:
        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "direction":
            raise Exception("Erro de sintaxe: Esperado DIREÇÃO após 'object'")
        
        direction_token = Parser.tokenizer.next

        Parser.tokenizer.select_next()
        
        if Parser.tokenizer.next.type != "relational_bool":
            raise Exception("Erro de sintaxe: Esperado RELATIONAL_BOOL ('is' ou 'is_not')")
        
        relational_bool_token = Parser.tokenizer.next

        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type in ["interactable", "state"]:
            object_target_token = Parser.tokenizer.next

            Parser.tokenizer.select_next()
        else:
            raise Exception("Erro de sintaxe: Esperado INTERACTABLE ou STATE em OBJECT_CONDITION")

        return ObjectCondition(None, [direction_token, relational_bool_token, object_target_token])

    @staticmethod
    def parse_loop_block() -> LoopBlock:
        Parser.tokenizer.select_next()
        
        loop_condition_node = Parser.parse_if_condition()
        
        if Parser.tokenizer.next.type != "colon":
            raise Exception("Erro de sintaxe: Esperado ':' após LOOP_CONDITION")
        
        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "line_break":
            raise Exception("Erro de sintaxe: Esperado nova linha após ':' no bloco de loop")
        
        Parser.tokenizer.select_next()

        loop_statements = []
        while Parser.tokenizer.next.type != "loop":
            loop_statements.append(Parser.parse_statement())

        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "end":
            raise Exception("Erro de sintaxe: Esperado 'end' após 'loop' tag")
        
        Parser.tokenizer.select_next()

        return LoopBlock(None, [loop_condition_node, loop_statements])

    @staticmethod
    def parse_collect_command() -> CollectCommand:
        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "iden":
            raise Exception("Erro de sintaxe: Esperado IDENTIFICADOR (key, coins, card) após 'collect'")
        
        collectable_token = Parser.tokenizer.next

        Parser.tokenizer.select_next()

        if Parser.tokenizer.next.type != "direction":
            raise Exception("Erro de sintaxe: Esperado DIREÇÃO após coletável")
        
        direction_token = Parser.tokenizer.next

        Parser.tokenizer.select_next()

        return CollectCommand(None, [collectable_token, direction_token])
    
    @staticmethod
    def run(filename):
        code = PrePro.filter(filename)

        Parser.tokenizer = Tokenizer(code, 0, Token("", ""))

        Parser.tokenizer.select_next()

        ast = Parser.parse_program()

        return ast


def main():
    filename = sys.argv[1]

    st = SymbolTable()

    ast = Parser.run(filename)

    ast.evaluate(st=st)

if __name__ == "__main__":
    main()