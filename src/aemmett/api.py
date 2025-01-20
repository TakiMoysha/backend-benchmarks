import orjson

from emmett import app

from shared.services import HealthService, OrderService


@app.route("/health")
async def h():
    data = HealthService().health()
    return orjson.dumps(data)


@app.route("/orders/")
async def orders_page():
    data = OrderService().orders_page()
    return orjson.dumps(data)
