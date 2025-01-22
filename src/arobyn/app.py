import structlog

from robyn import Config, Request, Robyn
from arobyn.router import router

logger = structlog.get_logger()


def create_app(processes: int = 1, workers: int = 1) -> Robyn:
    config = Config()
    config.processes = processes
    config.workers = workers

    logger.info("Config: ", config={**config.__dict__})
    app = Robyn(__file__, config=config)
    app.include_router(router)

    @app.get("/")
    async def index(request: Request):
        return "Ok"

    return app
