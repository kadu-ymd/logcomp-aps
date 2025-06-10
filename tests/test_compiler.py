import pytest
import subprocess
import os

MAIN_SCRIPT_PATH = os.path.join(os.path.dirname(__file__), '..', 'main.py')

TEST_PROGRAMS_DIR = os.path.join(os.path.dirname(__file__), '..', 'test_programs')

# Dicionário mapeando o nome do arquivo de teste para a saída esperada
# ATENÇÃO: As saídas foram REVISADAS para corresponder exatamente ao comportamento
# do seu `main.py` mais recente e às correções de inicialização nos arquivos .txt.
EXPECTED_OUTPUTS = {
    "move_test.txt": """Moving up for 10 units.
Moving right for 5 units.
Moving down for 3 units.
Moving left for 7 units.
""",
    "assignment_interact_test.txt": """Interaction to open on direction right.
""",
    "sequence_test.txt": """Moving up for 2 units.
Collecting 'key' in direction 'up'.
First 'key' collected!
Interaction to open on direction left.
Moving down for 1 units.
""",
    "if_collect_test.txt": """Collecting 'key' in direction 'up'.
First 'key' collected!
Moving right for 1 units.
""",
    "if_object_test.txt": """Verifying if object at 'up' 'is' 'locked'.
Interaction to open on direction up.
""",
    "if_bool_test.txt": """Interaction to open on direction right.
Moving up for 1 units.
""",
    # Saída ajustada para while_test.txt com 'key < 3' no .txt
    "while_test.txt": """Collecting 'key' in direction 'up'.
First 'key' collected!
Collecting 'key' in direction 'up'.
key now is: 2
Moving up for 1 units.
""",
    "collect_test.txt": """Collecting 'coins' in direction 'right'.
First 'coins' collected!
Collecting 'card' in direction 'down'.
First 'card' collected!
Collecting 'key' in direction 'up'.
First 'key' collected!
""",
    # NOVO TESTE DE INTEGRAÇÃO COMPLETO
    # Importante: A saída para o teste de integração deve ser gerada EXATAMENTE
    # executando `python main.py test_programs/full_integration_test.txt`
    # E copiando o output. A string abaixo é uma projeção e pode precisar de ajuste fino.
    "full_test.txt": """Moving up for 10 units.
Moving right for 5 units.
Moving down for 3 units.
Moving left for 7 units.
Interaction to open on direction right.
Collecting 'coins' in direction 'right'.
First 'coins' collected!
Collecting 'card' in direction 'down'.
First 'card' collected!
Collecting 'key' in direction 'up'.
First 'key' collected!
Moving up for 2 units.
Collecting 'key' in direction 'up'.
key now is: 2
Interaction to open on direction left.
Moving down for 1 units.
Moving right for 1 units.
Verifying if object at 'up' 'is' 'locked'.
Interaction to open on direction up.
Moving up for 1 units.
Collecting 'key' in direction 'up'.
key now is: 3
Moving up for 1 units.
""",
}

@pytest.mark.parametrize("test_file, expected_output", EXPECTED_OUTPUTS.items())
def test_compiler_output(test_file, expected_output):
    """
    Testa a saída do compilador para um programa de teste específico.
    """
    file_path = os.path.join(TEST_PROGRAMS_DIR, test_file)

    if not os.path.exists(file_path):
        pytest.fail(f"Arquivo de teste não encontrado: {file_path}")

    actual_stdout = ""
    actual_stderr = ""
    return_code = -1

    try:
        result = subprocess.run(
            ["python", MAIN_SCRIPT_PATH, file_path],
            capture_output=True,
            text=True,
            check=False,
            encoding="utf-8",
            errors="replace"
        )
        actual_stdout = result.stdout if result.stdout is not None else ""
        actual_stderr = result.stderr if result.stderr is not None else ""
        return_code = result.returncode

        if return_code != 0:
            pytest.fail(f"Programa '{test_file}' retornou código de erro {return_code}.\n"
                        f"Stdout: {actual_stdout}\n"
                        f"Stderr: {actual_stderr}")

    except FileNotFoundError:
        pytest.fail(f"Comando 'python' ou '{MAIN_SCRIPT_PATH}' não encontrado. "
                    "Verifique se Python está no PATH e se o caminho do script está correto.")
    except Exception as e:
        pytest.fail(f"Ocorreu uma exceção inesperada ao executar '{test_file}': {e}\n"
                    f"Stdout: {actual_stdout}\n"
                    f"Stderr: {actual_stderr}")

    normalized_actual_output = actual_stdout.replace('\r\n', '\n')
    normalized_expected_output = expected_output.replace('\r\n', '\n')

    assert normalized_actual_output.strip() == normalized_expected_output.strip(), \
        f"Saída incorreta para '{test_file}'.\n" \
        f"Esperado (normalizado):\n'{normalized_expected_output.strip()}'\n" \
        f"Recebido (normalizado):\n'{normalized_actual_output.strip()}'\n" \
        f"Esperado (repr original): {repr(expected_output)}\n" \
        f"Recebido (repr original): {repr(actual_stdout)}\n" \
        f"Stderr (se houver):\n'{actual_stderr}'\n" \
        f"Return Code: {return_code}"

def test_syntax_error_handling():
    """
    Testa se o compilador lida com erros de sintaxe esperados.
    """
    error_program_content = """
enter
move invalid_direction 10
program end
"""
    error_file_path = os.path.join(TEST_PROGRAMS_DIR, "syntax_error_test.txt")
    
    os.makedirs(TEST_PROGRAMS_DIR, exist_ok=True) 

    with open(error_file_path, "w", encoding="utf-8") as f:
        f.write(error_program_content)

    actual_stdout = ""
    actual_stderr = ""
    return_code = -1

    try:
        result = subprocess.run(
            ["python", MAIN_SCRIPT_PATH, error_file_path],
            capture_output=True,
            text=True,
            check=False,
            encoding="utf-8",
            errors="replace"
        )
        actual_stdout = result.stdout if result.stdout is not None else ""
        actual_stderr = result.stderr if result.stderr is not None else ""
        return_code = result.returncode

        assert return_code != 0, f"Teste de erro de sintaxe falhou: programa não retornou erro (Return Code: {return_code}). Saída:\nStdout: {actual_stdout}\nStderr: {actual_stderr}"

        error_message_found = False
        if "Erro de sintaxe" in actual_stderr or "Erro" in actual_stderr:
            error_message_found = True
        elif "Erro de sintaxe" in actual_stdout or "Erro" in actual_stdout:
            error_message_found = True
        
        assert error_message_found, f"Mensagem de erro esperada não encontrada no Stderr ou Stdout.\nEsperado: 'Erro de sintaxe' ou 'Erro'\nReal Stderr:\n'{actual_stderr}'\nReal Stdout:\n'{actual_stdout}'"

    except Exception as e:
        pytest.fail(f"Ocorreu uma exceção inesperada durante o teste de erro de sintaxe: {e}\n"
                    f"Stdout: {actual_stdout}\n"
                    f"Stderr: {actual_stderr}")
    finally:
        if os.path.exists(error_file_path):
            os.remove(error_file_path)