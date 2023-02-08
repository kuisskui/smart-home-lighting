from fastapi import FastAPI, Body
import uvicorn
from typing import Union, Optional, List
from pydantic import BaseModel
from datetime import datetime, timedelta

FORMAT_DATETIME = "%Y/%m/%d %H:%M"


class Light(BaseModel):
    id: Union[int, str]
    status: bool   
    auto: bool
    brightness: int

app = FastAPI()


@app.get("/")
def root():
    return {"msg": "smart-home-lighting"}


@app.get("/tap/")
def send(light: Light):
    return {"light": light}
    


if __name__ == "__main__":
    uvicorn.run(app, host="127.0.0.1", port=8080)
