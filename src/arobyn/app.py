import structlog

from robyn import Config, Request, Robyn
from arobyn.router import router

logger = structlog.get_logger()


def create_app() -> Robyn:
    config = Config()

    app = Robyn(__file__, config=config)
    app.include_router(router)

    @app.get("/")
    async def index(request: Request):
        return "Ok"

    return app
