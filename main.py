import sys
from compiler import Parser, RootProgramNode
from vm import EscapeRoomVM

def main():
    if len(sys.argv) < 2:
        print("Uso: python main.py <arquivo_programa_escape> [arquivo_saida.txt]")
        sys.exit(1)

    program_file = sys.argv[1]
    output_file_name = None

    if len(sys.argv) > 2:
        output_file_name = sys.argv[2]

    if output_file_name:
        try:
            original_stdout = sys.stdout
            sys.stdout = open(output_file_name, 'w', encoding='utf-8')
            print(f"[COMPILER] Saída redirecionada para '{output_file_name}'")
        except IOError as e:
            sys.stdout = original_stdout
            print(f"Erro: Não foi possível abrir o arquivo de saída '{output_file_name}': {e}", file=sys.stderr)
            sys.exit(1)

    try:
        print(f"\n--- Compiling '{program_file}' ---")

        ast = Parser.run(program_file)
        print("--- Compilation successful! AST generated. ---")

        print("\n--- Initializing Escape Room VM ---")
        vm = EscapeRoomVM()

        print("\n--- Executing compiled program on VM ---")

        vm.execute_ast(ast)
        print("\n--- Program execution finished. ---")

        print("\n--- Game Status ---")
        if vm.escaped:
            print(f"[GAME] Great job! You have successfully ESCAPED the room!")
        else:
            print(f"[GAME] You have NOT yet escaped the room.")
            print(f"[GAME] Current player position: {vm.player_position}")
            print(f"[GAME] Current inventory: {vm.inventory}")
            print(f"[GAME] Keep trying to find the exit!")
            
    except Exception as e:
        print(f"Runtime error during VM execution: {e}")
        sys.exit(1)
    finally:
        if output_file_name:
            sys.stdout.close()
            sys.stdout = original_stdout
            print(f"\n[COMPILER] Saída finalizada. Verifique '{output_file_name}' para o log completo.")

if __name__ == "__main__":
    main()