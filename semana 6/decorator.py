import math
from functools import wraps


def validar_positivos(func):
    """Decorator que valida entrada positiva"""

    @wraps(func)  # Preserva metadatos de la función
    def wrapper(*args, **kwargs):
        if any(x <= 0 for x in args):
            raise ValueError("La función requiere valores positivos")

        print(f"[Validador] Entrada válida: {args[0]}")
        return func(*args, **kwargs)

    return wrapper


def logger(func):
    """Decorator que añade logging"""

    @wraps(func)
    def wrapper(*args, **kwargs):
        print(f"[Logger] Calculando para x = {args[0]}")
        resultado = func(*args, **kwargs)
        print(f"[Logger] Resultado: {resultado}")
        return resultado

    return wrapper


# Aplicar múltiples decoradores
@logger
@validar_positivos
def raiz_cuadrada(n: float) -> float:
    return math.sqrt(n)


if __name__ == "__main__":
    print("=== Decorator Pattern ===")

    print("\nPrueba con valor válido (25):")
    print(f"Resultado: {raiz_cuadrada(25)}")

    print("\nPrueba con valor inválido (-4):")
    try:
        print(f"Resultado: {raiz_cuadrada(-4)}")
    except ValueError as e:
        print(f"Error: {e}")

    print(f"\n[Nota] @wraps preserva: {raiz_cuadrada.__name__}")
