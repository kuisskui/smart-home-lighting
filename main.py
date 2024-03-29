from fastapi import FastAPI, Body, HTTPException
import uvicorn
from typing import Union, Optional, List
from pydantic import BaseModel
from fastapi.middleware.cors import CORSMiddleware

import data as data


class Id(BaseModel):
    id: str


class Light(BaseModel):
    id: Union[str, int]
    status: bool
    auto: int
    brightness: int
    ldr: int


app = FastAPI()

origins = ["*"]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.post("/")
def root():
    return {"msg": "smart-home-lighting"}


@app.post("/tap/send/")
def send(light: Id):
    return data.collection.find_one({"id": f"{light.id}"}, {"_id": False})

    # return {"light": server}


@app.get("/tap/send/{id}/")
def abobo(id: str):
    return data.collection.find_one({"id": str(id)}, {"_id": False})


@app.post("/tap/receive/")
def receive(light: Light):
    try:
        # find data
        info = data.collection.find({"id": str(light.id)}, {"_id": False})
        var = list(info)[0]
        ldr = var['ldr']  # default value on database
        auto = var['auto']  # default value on database
        brightness = var['brightness']  # default value on database
        # hardware
        if light.ldr >= 125 and auto == 1:
            data.collection.update_one({"id": str(light.id)},
                                       {"$set": {
                                           "id": str(light.id),
                                           "status": False,
                                           "auto": auto,
                                           "brightness": brightness,
                                           "ldr": light.ldr}})
        elif 0 <= light.ldr <= 124 and auto == 1:
            data.collection.update_one({"id": str(light.id)},
                                       {"$set": {
                                           "id": str(light.id),
                                           "status": True,
                                           "auto": auto,
                                           "brightness": brightness,
                                           "ldr": light.ldr}})
        else:  # front
            # update
            data.collection.update_one({"id": str(light.id)},
                                       {"$set": {
                                        "id": str(light.id),
                                        "status": light.status,
                                        "auto": light.auto,
                                        "brightness": light.brightness,
                                        "ldr": ldr}})
    except Exception:
        raise HTTPException(500, "ID not found")
    new_data = data.collection.find_one({"id": light.id}, {"_id": False})
    return {"light": new_data}


if __name__ == "__main__":
    uvicorn.run(app, host="127.0.0.1", port=8080)
