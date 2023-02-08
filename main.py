from fastapi import FastAPI, Body, HTTPException
import uvicorn
from typing import Union, Optional, List
from pydantic import BaseModel
import data as data


class Light(BaseModel):
    id: Union[str, int]
    status: bool
    auto: bool
    brightness: int
    ldr: int


app = FastAPI()


@app.get("/")
def root():
    return {"msg": "smart-home-lighting"}


@app.post("/tap/send/")
def send(light: Light):
    return {"light": light}


@app.post("/tap/receive/")
def receive(light: Light):
    try:
        # find data
        info = data.collection.find({"id": str(light.id)}, {"_id": False})
        var = list(info)[0]
        ldr = var['ldr']
        auto = var['auto']
        if ldr >= 125 and auto == True:
            data.collection.update_one({"id": str(light.id)},
                                       {"$set": {
                                           "id": str(light.id),
                                           "status": False,
                                           "auto": light.auto,
                                           "brightness": light.brightness,
                                           "ldr": light.ldr}})
        elif 0 <= ldr <= 124 and auto == True:
            data.collection.update_one({"id": str(light.id)},
                                       {"$set": {
                                           "id": str(light.id),
                                           "status": True,
                                           "auto": light.auto,
                                           "brightness": light.brightness,
                                           "ldr": light.ldr}})
        else:
            # update
            data.collection.update_one({"id": str(light.id)},
                                       {"$set": {
                                        "id": str(light.id),
                                        "status": light.status,
                                        "auto": light.auto,
                                        "brightness": light.brightness,
                                        "ldr": light.ldr}})
    except Exception:
        raise HTTPException(500, "ID not found")
    new_data = data.collection.find_one({"id": light.id}, {"_id": False})
    return {"light": new_data}


if __name__ == "__main__":
    uvicorn.run(app, host="127.0.0.1", port=8080)
