import sys
from compiler import Parser, RootProgramNode
from vm import EscapeRoomVM

def main():
    if len(sys.argv) < 2:
        print("Uso: python main.py <arquivo_programa_escape>")
        sys.exit(1)

    program_file = sys.argv[1]

    print(f"\n--- Compiling '{program_file}' ---")

    try:
        ast = Parser.run(program_file)
        print("--- Compilation successful! AST generated. ---")

    except Exception as e:
        print(f"Compilation error: {e}")
        sys.exit(1)

    print("\n--- Initializing Escape Room VM ---")
    vm = EscapeRoomVM()

    print("\n--- Executing compiled program on VM ---")

    try:
        vm.execute_ast(ast)
        print("\n--- Program execution finished. ---")
        
    except Exception as e:
        print(f"Runtime error during VM execution: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()