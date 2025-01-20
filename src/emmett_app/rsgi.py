from emmett import App, request, response
from emmett.orm import Database, Model, Field
from emmett.tools import service, requires


class Task(Model):
    name = Field.string()
    is_completed = Field.bool(default=False)


app = App(__name__)
app.config.auth.single_tempalte
app.config.db.uri = "sqlite::memory:"
db = Database(app)
db.define_models(Task)
app.pipeline = [db.pipe]


def is_authenticated():
    return request.headers.get("X-Auth") == "secret"


def not_authenticated():
    response.status = 401
    return {"message": "Not authenticated"}


@app.route("/")
@requires(is_authenticated, otherwise=not_authenticated)
async def todo():
    page = request.query_params.page or 1
    tasks = Task.where(lambda t: not t.is_completed).select(paginate=(page, 20))
    return {"tasks": tasks}


import orjson

from shared.services import HealthService, OrderService


@app.route("/api/health")
async def h():
    data = HealthService().health()
    return orjson.dumps(data)


@app.route("/api/orders")
async def orders_page():
    data = OrderService().orders_page()
    return orjson.dumps(data)
