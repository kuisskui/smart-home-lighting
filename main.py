from fastapi import FastAPI, Body
import uvicorn
from typing import Union, Optional, List
from pydantic import BaseModel
from datetime import datetime, timedelta

import backend.data as data
FORMAT_DATETIME = "%Y/%m/%d %H:%M"

class Id(BaseModel):
    id: str

class Light(BaseModel):
    id: Union[int, str]
    status: bool   
    auto: bool
    brightness: int
    ldr: int

app = FastAPI()


@app.post("/")
def root():
    return {"msg": "smart-home-lighting"}

@app.post("/tap/send/")
def send(light: Id):
    return data.collection.find_one({"id":f"{light.id}"}, {"_id": False})

    # return {"light": server}

@app.post("/tap/receive")
def receive(light: Light):
    """บันทึกลงdatabase"""
    return {"light": light}    


if __name__ == "__main__":
    uvicorn.run(app, host="127.0.0.1", port=8080)
