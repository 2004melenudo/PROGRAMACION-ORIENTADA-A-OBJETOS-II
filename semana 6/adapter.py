class PasarelaUSD:
    def procesar_pago(self, monto_usd: float) -> str:
        return f"Cobrado {monto_usd:.2f} USD"


class AdaptadorSoles:
    """Adapter que convierte Soles a USD"""

    def __init__(self, pasarela: PasarelaUSD, tasa: float = 3.70):
        self.pasarela = pasarela   # Composición
        self.tasa = tasa

    def procesar_pago_soles(self, monto_pen: float) -> str:
        # Conversión: interfaz incompatible -> compatible
        usd = monto_pen / self.tasa
        return self.pasarela.procesar_pago(usd)


if __name__ == "__main__":
    print("=== Adapter Pattern ===")

    api_usd = PasarelaUSD()
    adapter = AdaptadorSoles(api_usd, 3.70)

    print(f"Pago en soles (100 PEN): {adapter.procesar_pago_soles(100.0)}")

    print("\n[Nota] Python permite duck typing:")
    print("No necesitas heredar de interfaz específica.")
