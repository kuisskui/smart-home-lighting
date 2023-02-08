import { Dispatch, SetStateAction } from "react";
import { Room } from "../../pages";

type CardProps = {
  room: Room;
  setRoom: Dispatch<SetStateAction<Room>>;
};

const Card: React.FC<CardProps> = ({ room, setRoom }) => {
  return (
    <div className="card h-[450px] w-96 bg-base-100 shadow-xl">
      <figure className="h-96 px-10 pt-10">
        <label className="swap swap-flip text-9xl ">
          <input
            type="checkbox"
            checked={room?.isOn}
            onClick={() => setRoom({ ...room, isOn: !room.isOn })}
          />
          <div className="swap-on">🌝</div>
          <div className="swap-off">🌚</div>
        </label>
      </figure>
      <div className="card-body items-center text-center">
        <h2 className="card-title mb-8 text-3xl">{`${room.name}  ${
          room.isOn ? "on" : "off"
        } ${room.brightness} %`}</h2>
        <div className="card-actions items-center justify-center gap-5">
          <input
            type="range"
            min="0"
            max="100"
            value={room.brightness}
            onChange={(e) =>
              setRoom({
                ...room,
                brightness:
                  parseInt(e.target.value) > 20 ? parseInt(e.target.value) : 20,
              })
            }
            className="range range-warning"
            step="25"
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
    </div>
  );
};

export default Card;
