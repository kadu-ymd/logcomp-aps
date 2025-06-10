import sys
import re


VAR_PATTERN = "[a-zA-Z]([a-zA-Z]|_|[0-9])*"

DIRECTION = ["up", "right", "down", "left"]

RELATIONAL_BOOL = ["is", "is_not"]

COLLECTABLE = ["key", "coins", "card"]

INTERACTABLE = ["locker", "closet", "desk", "exit_door"]

STATE = ["locked", "unlocked"]

RESERVED_WORDS = ["enter", "end", "end_program", "if", "else", "move", "interact", "open", "collect", "define", "sequence", "conditional", "object", "while", "loop", "is", "is_not", "up", "right", "down", "left", "key", "coins", "card", "locker", "closet", "desk", "exit_door", "locked", "unlocked", "program"]


class SymbolTable:
    def __init__(self, parent = None):
        self.table = dict()
        self.parent = parent

    def create(self, key: str, value):
        if key not in self.table:
            self.table[key] = value
        else:
            raise Exception(f"Variable '{key}' already declared")

    def get(self, key):
        if key in self.table:
            return self.table[key]
        elif self.parent is not None:
            return self.parent.get(key)
        else:
            raise Exception(f"Variable '{key}' not defined")

    def set(self, key, value):
        if key in self.table:
            self.table[key] = value
        elif self.parent is not None:
            self.parent.set(key, value)
        else:
            raise Exception(f"Variable '{key}' not declared")


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
        """Gets the next Token at the target file.
        """
        value = []

        # While not EOF, tries to define a Token
        if self.position != len(self.source):
            # Ignore blank spaces
            while (self.source[self.position] == " "):
                self.position += 1

            # Iterate through the file characters
            for i in range(self.position, len(self.source) + 1):
                self.position = i

                if (self.source[i].isdigit() or self.source[i].isalpha()
                        or self.source[i] == "_"):
                    value.append(self.source[i])
                else:
                    break

            try:
                # If list "value" is empty, no alphanumeric + underscore characters were found in the current Token
                if not len(value):
                    # Assignment
                    if (self.source[self.position] == "="):
                        self.next = Token("assignment", "=")

                    # Line break
                    if (self.source[self.position] == "\n"):
                        self.next = Token("line_break", None)

                    # Relational operators
                    ## Greater than
                    if (self.source[self.position] == ">"):
                        self.next = Token("gt", None)
                        self.position += 1

                    ## Less than
                    if (self.source[self.position] == "<"):
                        self.next = Token("lt", None)
                        self.position += 1

                    ## Greater equal than
                    if (self.source[self.position:self.position + 2] == ">="):
                        self.next = Token("ge", None)
                        self.position += 1

                    ## Less equal than
                    if (self.source[self.position:self.position + 2] == "<="):
                        self.next = Token("le", None)
                        self.position += 1

                    ## Equal to
                    if (self.source[self.position:self.position + 2] == "=="):
                        self.next = Token("equal", None)
                        self.position += 1

                    self.position += 1

                # Else, it means that the Token is a identifier, reserved word or a number
                else:
                    val = "".join(value)

                    # Matches the regex pattern (not a number)
                    if re.match(VAR_PATTERN, val, flags=0):
                        # Identifier
                        if val not in RESERVED_WORDS:
                            self.next = Token("iden", val)

                        # Direction
                        elif val in DIRECTION:
                            self.next = Token("direction", val)

                        # Collectable
                        elif val in COLLECTABLE:
                            self.next = Token("collectable", val)

                        # Interactable
                        elif val in INTERACTABLE:
                            self.next = Token("interactable", val)

                        # State
                        elif val in STATE:
                            self.next = Token("state", val)

                        # Other word (reserved or not declared (results in error))
                        else:
                            self.next = Token(f"{val}", None)

                    # Does NOT match the regex pattern (probably a number)
                    else:
                        try:
                            self.next = Token("int", int(val))
                        except ValueError:
                            raise Exception(f"Token inválido: {val}")

            except Exception as e:
                raise Exception(f"Erro -> {e}")

        else:
            self.next = Token("EOF", None)

        # print(f"Token({self.next.type}, {self.next.value})")


class Node:
    def __init__(self, value, children: list):
        self.value = value
        self.children = children

    def evaluate(self, st: SymbolTable): ...

class BinOp(Node):
    def evaluate(self, st):
        child_0, child_1 = self.children

        child_tuple_0 = child_0.evaluate(st)
        child_tuple_1 = child_1.evaluate(st)

        if self.value == "+":
            if child_tuple_0[0] == "int" and child_tuple_1[0] == "int":
                return ("int", child_tuple_0[1] + child_tuple_1[1], False)
            else:
                return ("string", str(child_tuple_0[1]).lower() + str(child_tuple_1[1]).lower(), False)

        if self.value == "-":
            if child_tuple_0[0] == "int" and child_tuple_1[0] == "int":
                return ("int", child_tuple_0[1] - child_tuple_1[1], False)
            else:
                raise Exception("erro de tipo -> precisa ser int (binop)")

        if self.value == "*":
            if child_tuple_0[0] == "int" and child_tuple_1[0] == "int":
                return ("int", child_tuple_0[1] * child_tuple_1[1], False)
            else:
                raise Exception("erro de tipo -> precisa ser int (binop)")

        if self.value == "/":
            if child_tuple_0[0] == "int" and child_tuple_1[0] == "int":
                return ("int", child_tuple_0[1] // child_tuple_1[1], False)
            else:
                raise Exception("erro de tipo -> precisa ser int (binop)")

        if self.value == "&&":
            if child_tuple_0[0] == "bool" and child_tuple_1[0] == "bool":
                return ("bool", child_tuple_0[1] and child_tuple_1[1], False)
            else:
                raise Exception("erro de tipo -> precisa ser bool (binop)")

        if self.value == "||":
            if child_tuple_0[0] == "bool" and child_tuple_1[0] == "bool":
                return ("bool", child_tuple_0[1] or child_tuple_1[1], False)
            else:
                raise Exception("erro de tipo -> precisa ser bool (binop)")

        if self.value == ">":
            if child_tuple_0[0] == child_tuple_1[0]:
                return ("bool", child_tuple_0[1] > child_tuple_1[1], False)
            else:
                raise Exception("erro de tipo -> precisa ser igual (binop)")

        if self.value == "<":
            if child_tuple_0[0] == child_tuple_1[0]:
                return ("bool", child_tuple_0[1] < child_tuple_1[1], False)
            else:
                raise Exception("erro de tipo -> precisa ser igual (binop)")

        if self.value == "==":
            if child_tuple_0[0] == child_tuple_1[0]:
                return ("bool", child_tuple_0[1] == child_tuple_1[1], False)
            else:
                raise Exception("erro de tipo -> precisa ser igual (binop)")


class UnOp(Node):
    def evaluate(self, st):
        for child in self.children:
            child_tuple = child.evaluate(st)

            if self.value == "+":
                if child_tuple[0] == "int":
                    return (child_tuple[0], child_tuple[1])
                else:
                    raise Exception("Operator must be followed by an integer")

            if self.value == "-":
                if child_tuple[0] == "int":
                    return (child_tuple[0], -child_tuple[1])
                else:
                    raise Exception("Operator must be followed by an integer")

            if self.value == "!":
                if child_tuple[0] == "bool":
                    return (child_tuple[0], not child_tuple[1])
                else:
                    raise Exception("Operator must be followed by a boolean")

# Nós para os tipos de variáveis
class IntVal(Node):
    def evaluate(self, st):
        return ("int", self.value, False)


class StrVal(Node):
    def evaluate(self, st):
        return ("string", self.value, False)


class BoolVal(Node):
    def evaluate(self, st):
        return ("bool", self.value, False)


class NoOp(Node): ...


class Identifier(Node):
    def evaluate(self, st):
        try:
            return st.get(self.value)
        except Exception as e:
            raise Exception(f"Error -> {e}")


class Assignment(Node):
    def evaluate(self, st):
        var_iden, val_node = self.children

        node_eval = val_node.evaluate(st)

        dec_type = st.get(key=var_iden) # verifica se a variável existe

        if node_eval[0] == dec_type[0]:
            st.set(key=var_iden, value=node_eval)
        else:
            raise Exception(f"valor da atribuição precisa ser o mesmo que foi declarado (assignment)")


class Block(Node):
    def evaluate(self, st):
        for child in self.children:
            if isinstance(child, Return):
                return child.evaluate(st)

            elif isinstance(child, Block):
                st_chained = SymbolTable(st)
                child.evaluate(st_chained)

            elif isinstance(child, If):
                return_value = child.evaluate(st)

                if return_value != None:
                    return return_value

            elif isinstance(child, For):
                return_value = child.evaluate(st)

                if return_value != None:
                    return return_value

            else:
                child.evaluate(st)


class For(Node):
    def evaluate(self, st):
        _type, _, _ = self.children[0].evaluate(st)
        return_value = None

        if _type != "bool":
            raise Exception(f"Incompatible type for condition (-> {_type}) in for-loop")

        while self.children[0].evaluate(st)[1]:
            return_value = self.children[1].evaluate(st)

            if return_value != None:
                return return_value


class If(Node):
    def evaluate(self, st):
        _type, cond, _ = self.children[0].evaluate(st)
        return_value = None

        if _type != "bool":
            raise Exception(f"Incompatible type for condition -> {_type} in if-clause")

        if len(self.children) == 3:
            if cond:
                return_value = self.children[1].evaluate(st) # bloco de código do if

                if return_value != None: return return_value
            else:
                return_value = self.children[2].evaluate(st) # bloco de código do else

                if return_value != None: return return_value
        else:
            if cond:
                return_value = self.children[1].evaluate(st) # bloco de código do if

                if return_value != None: return return_value


class VarDec(Node):
    def evaluate(self, st):
        var_identifier = self.children[0].value
        vardec_type = self.value

        if len(self.children) > 1:
            var_type, var_value, _ = self.children[1].evaluate(st) # evaluate do BinOp

            if vardec_type == var_type:
                st.create(key=var_identifier, value=(var_type, var_value, False))

            else:
                raise Exception("tipos incompatíveis -> declaração de variáveis (vardec)")
        else:
            st.create(key=var_identifier, value=(vardec_type, None, False))


class FuncDec(Node):
    def evaluate(self, st):
        return st.create(self.children[0], (self.value, self, True))


class FuncCall(Node):
    def evaluate(self, st):
        func_declaration = st.get(self.value) # VERIFY IF FUNCTION WAS DECLARED

        if func_declaration[2]: # IS FUNCTION?
            node_funcdec = func_declaration[1] # REFERENCE TO FUNCDEC NODE

            if len(node_funcdec.children) - 2 == len(self.children): # VERIFY NUMBER OF ARGUMENTS IN FUNCDEC (funcdec.children - 2) AND FUNCCALL (self.children)
                st_chained = SymbolTable(st)

                funcdec_arguments = node_funcdec.children[1:-1]

                for i in range(len(self.children)): # ITERATE OVER ARGUMENTS
                    call_arg = self.children[i].evaluate(st)
                    declaration_arg = funcdec_arguments[i]

                    if call_arg[0] == declaration_arg.value:
                        st_chained.create(declaration_arg.children[0], (declaration_arg.value, call_arg[1], False))

                node_block = node_funcdec.children[-1]

                return_value = node_block.evaluate(st_chained) # EVALUATES BLOCK FROM FUNCDEC

                if return_value == None and func_declaration[0] != None:
                    raise Exception(f"Function expected return type '{func_declaration[0]}', not 'void'")

                elif return_value != None and return_value[0] != func_declaration[0]:
                    raise Exception(f"Function expected return type '{func_declaration[0]}', not '{return_value[0]}'")

                elif return_value != None:
                    return return_value


class Return(Node):
    def evaluate(self, st):
        return self.children[0].evaluate(st)


# New nodes
class Program(Node):
    def evaluate(self, st):
        for child in self.children:
            child.evaluate()


class Movement(Node):
    # First child -> direction
    # Second child -> value
    def evaluate(self, st):
        ...


class Interact(Node):
    def evaluate(self, st):
        return super().evaluate(st)
    

class Collect(Node):
    def evaluate(self, st):
        return super().evaluate(st)


class Direction(Node):
    def evaluate(self, st):
        return self.value


class StepValue(Node):
    def evaluate(self, st):
        return self.value


class Action(Node):
    def evaluate(self, st):
        return self.value


class Collectable(Node):
    def evaluate(self, st):
        return super().evaluate(st)


class Parser:
    tokenizer: Tokenizer

    @staticmethod
    def parse_program():
        node = Program(None, [])

        if Parser.tokenizer.next.type == "enter":
            Parser.tokenizer.select_next()

            if Parser.tokenizer.next.type == "line_break":
                Parser.tokenizer.select_next()

                while Parser.tokenizer.next.type != "program":
                    node.children.append(Parser.parse_statement())

                if Parser.tokenizer.next.type == "end":
                    Parser.tokenizer.select_next()

                    # Raises exception if no line break was found after "enter"
                    if Parser.tokenizer.next.type != "line_break":
                        raise Exception("'enter' keyword must be followed by a line break")
                        
            # Raises exception if no line break was found after "enter"
            else:
                raise Exception("'enter' keyword must be followed by a line break")

        # Raises exception if program does NOT start with "enter"
        else:
            raise Exception("Program MUST start with 'enter' keyword")
        
        return node

    @staticmethod
    def parse_statement() -> Node:
        node = Node(None, [])

        if Parser.tokenizer.next.type == "move":
            node = Movement(None, [])

            Parser.tokenizer.select_next()

            if Parser.tokenizer.next.type == "direction":
                node.children.append(Direction(Parser.tokenizer.next.value, []))

                Parser.tokenizer.select_next()

                if Parser.tokenizer.next.type == "int":
                    node.children.append(StepValue(Parser.tokenizer.next.value, []))

                Parser.tokenizer.select_next()

            else:
                raise Exception(f"'{Parser.tokenizer.next.type}' is not a valid direction")

        elif Parser.tokenizer.next.type == "interact":
            node = Interact(None, [])

            Parser.tokenizer.select_next()

            if Parser.tokenizer.next.type == "open" or Parser.tokenizer.next.type == "collect":
                node.children.append(Action(Parser.tokenizer.next.type, []))
                
                Parser.tokenizer.select_next()

                if Parser.tokenizer.next.type == "direction":
                    node.children.append(Direction(Parser.tokenizer.next.type, []))

                    Parser.tokenizer.select_next()

                else:
                    raise Exception(f"'{Parser.tokenizer.next.value}' is not a valid direction")
            
            else:
                raise Exception(f"'{Parser.tokenizer.next.type}' is not a valid action")

        elif Parser.tokenizer.next.type == "collect":
            node = Collect(None, [])

            Parser.tokenizer.select_next()

            if Parser.tokenizer.next.type == "collectable":
                node.children.append(Collectable(Parser.tokenizer.next.value, []))

                Parser.tokenizer.select_next()

                if Parser.tokenizer.next.type == "direction":
                    node.children.append(Direction(Parser.tokenizer.next.value, []))
                    
                    Parser.tokenizer.select_next()

        elif Parser.tokenizer.next.type == "define":
            node = FuncDec(None, [])

        elif Parser.tokenizer.next.type == "if":
            ...

        elif Parser.tokenizer.next.type == "while":
            ...

        elif Parser.tokenizer.next.type == "iden":
            ...

        else:
            node = NoOp(None, [])

        Parser.tokenizer.select_next()
        
        return node

    @staticmethod
    def run(filename):
        code = PrePro.filter(filename)

        Parser.tokenizer = Tokenizer(code, 0, Token("", ""))

        Parser.tokenizer.select_next()

        ast = Parser.parse_program()

        ast.children.append(FuncCall("main", []))

        return ast


def main():
    filename = sys.argv[1]

    code = PrePro.filter(filename)

    Parser.tokenizer = Tokenizer(code, 0, Token("", ""))

    Parser.tokenizer.select_next()

    print(Parser.parse_program().children)

    # ast = Parser.run(filename)

    # st = SymbolTable()

    # ast.evaluate(st=st)


if __name__ == "__main__":
    main()
