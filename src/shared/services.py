from datetime import datetime

from .models import Order, OrdersPage


class HealthService:
    def health(self):
        data = {
            "request": "ok",
            "database": "ok",
            "cache": "ok",
        }
        return data


class OrderService:
    def orders_page(self):
        page_size = 10
        orders = [
            Order(
                symbol=str(k),
                instrument_id=str(k),
                side="buy",
                volume=50,
                start_time=datetime.now().isoformat(timespec="milliseconds"),
                end_time=datetime.now().isoformat(timespec="milliseconds"),
            )
            for k in range(10)
        ]

        data = OrdersPage(number=1, size=page_size, content=orders)
        return data
