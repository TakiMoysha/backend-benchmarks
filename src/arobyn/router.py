import orjson
from robyn import Response, SubRouter

from shared.services import HealthService, OrderService

router = SubRouter(__file__)


@router.get("/api/health")
async def h():
    data = HealthService().health()
    return Response(
        status_code=200,
        headers={"content-type": "application/json"},
        description=orjson.dumps(data),
    )


@router.get("/api/orders")
async def orders_page():
    data = OrderService().orders_page()
    return Response(
        status_code=200,
        headers={"content-type": "application/json"},
        description=orjson.dumps(data),
    )
