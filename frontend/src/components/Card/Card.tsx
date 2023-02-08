import axios from "axios";
import { Dispatch, SetStateAction, useState } from "react";
import { useEffect } from "react";
import type { Room } from "../../pages";

type CardProps = {
  room: Room;
  setRoom: Dispatch<SetStateAction<Room>>;
};

const Card: React.FC<CardProps> = ({ room, setRoom }) => {
  const [nowOutput, setNowOutput] = useState<Omit<Room, "name">>(room);

  // get server status every 0.5 second
  // const interval = setInterval(() => {
  //   axios
  //     .get(`http://localhost:8000/api/getLight/${room.id}`)
  //     .then((res) => {
  //       const data = res.data as Omit<Room, "name">;

  //       if (data.status !== room.status) {
  //         setRoom({ ...room, status: data.status });
  //       }
  //     })
  //     .catch((err) => {
  //       console.log(err);
  //     });
  // }, 500);

  // useEffect(() => {
  //   return () => {
  //     clearInterval(interval);
  //   };
  // }, [interval]);

  useEffect(() => {
    setNowOutput({
      id: room.id,
      status: room.status,
      auto: room.auto,
      brightness: (room.brightness / 100) * 255,
      ldr: -1,
    });

    axios
      .post("http://localhost:8000/api/setLight", {
        id: room.id,
        status: room.status,
        auto: room.auto,
        brightness: (room.brightness / 100) * 255,
        ldr: -1,
      })
      .then((res) => {
        console.log(res.data);
      })
      .catch((err) => {
        console.log(err);
      });
  }, [room]);

  return (
    <div className="card h-[450px] w-96 bg-base-100 shadow-xl">
      <figure className="h-96 overflow-visible px-10  pt-10">
        <label className="swap swap-flip text-9xl ">
          <input
            type="checkbox"
            defaultChecked={room?.status}
            disabled={room?.auto}
            onClick={() => setRoom({ ...room, status: !room.status })}
          />
          <div className="swap-on flex items-center justify-center ">
            <img
              className="m-auto h-32 w-32 drop-shadow-[0_0px_40px_rgba(255,240,0,0.65)]"
              src="https://images.emojiterra.com/google/noto-emoji/v2.034/512px/1f4a1.png"
              alt=""
            />
          </div>
          <div className="swap-off flex items-center justify-center">
            <img
              className="m-auto h-32 w-32 grayscale-[70%] "
              src="https://images.emojiterra.com/google/noto-emoji/v2.034/512px/1f4a1.png"
              alt=""
            />
          </div>
        </label>
      </figure>
      <div className="card-body items-center text-center">
        <h2 className="card-title mb-8 text-3xl">{`${room.name}  ${
          room.status ? "on" : "off"
        } ${room.brightness} %`}</h2>
        <div className="card-actions items-center justify-center gap-5">
          <input
            type="range"
            min="20"
            max="100"
            value={room.brightness}
            onChange={(e) =>
              setRoom({
                ...room,
                brightness: Number(e.target.value),
              })
            }
            className="range range-warning"
            step="20"
          />
          <div className="flex w-full justify-between px-2 text-xs">
            <span>|</span>
            <span>|</span>
            <span>|</span>
            <span>|</span>
            <span>|</span>
          </div>
          <div className="form-control w-52">
            <label className="label cursor-pointer">
              <span className="label-text">
                auto light {room.auto ? "on" : "off"}
              </span>
              <input
                type="checkbox"
                className="toggle-success toggle "
                defaultChecked={room.auto}
                onClick={() => setRoom({ ...room, auto: !room.auto })}
              />
            </label>
          </div>
        </div>
      </div>
      <pre>
        <code>{JSON.stringify(nowOutput, null, 2)}</code>
      </pre>
    </div>
  );
};

export default Card;
