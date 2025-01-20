from abc import ABC
from typing import Callable, Any, TypeVar

import rsgi_lib


Fn = TypeVar("Fn", bound=Callable[..., Any])
FnEventHandler = Callable[[int, str, str], None]


def define_event(name: str) -> Callable[[Fn], Fn]:
    def inner(func: Fn) -> Fn:
        def wrapper(user_id: int, username: str, email: str) -> Any:
            print("event", name, "called with args:", user_id, username, email)
            return func(user_id, username, email)

        return wrapper  # type:ignore

    return inner


@define_event("test")
def on_user_registered(user_id: int, username: str) -> None:
    print("user registered: ", user_id, username)


_ValueType_co = TypeVar("_ValueType_co", covariant=True)
_NewValueType = TypeVar("_NewValueType")


class DefineEvent(ABC):
    def bind(
        fn: Callable[[_ValueType_co], "DefineEvent" | FnEventHandler],
    ) -> "DefineEvent[FnEventHandler]": ...


@DefineEvent.bind
def on_user_registered(user_id: int, username: str) -> None:
    print("user registered: ", user_id, username)
