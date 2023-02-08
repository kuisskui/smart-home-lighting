import { Dispatch, SetStateAction, useState } from "react";
import { useEffect } from "react";
import type { Room } from "../../pages";

type CardProps = {
  room: Room;
  setRoom: Dispatch<SetStateAction<Room>>;
};

const Card: React.FC<CardProps> = ({ room, setRoom }) => {
  const [nowOutput, setNowOutput] = useState<Omit<Room, "name">>(room);

  useEffect(() => {
    setNowOutput({
      id: room.id,
      isOn: room.isOn,
      isAuto: room.isAuto,
      brightness: (room.brightness / 100) * 255,
    });
  }, [room]);
  return (
    <div className="card h-[450px] w-96 bg-base-100 shadow-xl">
      <figure className="h-96 overflow-visible px-10  pt-10">
        <label className="swap swap-flip text-9xl ">
          <input
            type="checkbox"
            checked={room?.isOn}
            disabled={room?.isAuto}
            onClick={() => setRoom({ ...room, isOn: !room.isOn })}
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
          room.isOn ? "on" : "off"
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
                auto light {room.isAuto ? "on" : "off"}
              </span>
              <input
                type="checkbox"
                className="toggle-success toggle "
                checked={room.isAuto}
                onClick={() => setRoom({ ...room, isAuto: !room.isAuto })}
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
