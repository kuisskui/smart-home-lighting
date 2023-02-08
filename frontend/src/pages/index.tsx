import { type NextPage } from "next";
import Head from "next/head";
import Link from "next/link";
import { useState } from "react";
import Card from "../components/Card/Card";

export type Room = {
  name: string;
  isOn: boolean;
  isAuto: boolean;
  brightness: number;
};

const Home: NextPage = () => {
  const [roomOne, setRoomOne] = useState<Room>({
    name: "living room",
    isOn: false,
    isAuto: false,
    brightness: 20,
  });

  const [roomTwo, setRoomTwo] = useState<Room>({
    name: "bedroom",
    isOn: false,
    isAuto: false,
    brightness: 20,
  });

  const [roomThree, setRoomThree] = useState<Room>({
    name: "kitchen",
    isOn: false,
    isAuto: false,
    brightness: 20,
  });

  return (
    <>
      <Head>
        <title>Create T3 App</title>
        <meta name="description" content="Generated by create-t3-app" />
        <link rel="icon" href="/favicon.ico" />
      </Head>
      <main className="flex min-h-screen items-center justify-center gap-10 bg-gradient-to-b from-[#2e026d] to-[#15162c]">
        <Card room={roomOne} setRoom={setRoomOne} />
        <Card room={roomTwo} setRoom={setRoomTwo} />
        <Card room={roomThree} setRoom={setRoomThree} />
      </main>
    </>
  );
};

export default Home;
