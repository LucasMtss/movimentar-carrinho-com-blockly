import { useEffect, useState } from "react";
import Car from "../../components/Car";
import io from "socket.io-client";
import { Container, Street } from "./style";
import { Movimentos } from "../../interfaces/constantes";

function Home() {
  const [rotate, setRotate] = useState(Movimentos.frente);
  const [marginTop, setMarginTop] = useState(0);
  const [marginRight, setMarginRight] = useState(0);
  const [marginBottom, setMarginBottom] = useState(0);
  const [marginLeft, setMarginLeft] = useState(0);
  const [movimentos, setMovimentos] = useState([]);
  const MOVEMENT_SIZE = 60;

  function resetMoviments() {
    setMarginTop(0);
    setMarginBottom(0);
    setMarginLeft(0);
    setMarginRight(0);
    setRotate(0);
  }

  async function executeMoviments(moviments: string[] | undefined) {
    if (!moviments) return;
    setTimeout(() => {
      if (moviments[0] === "frente") {
        setRotate(0);
        setMarginLeft((oldValue) => oldValue + MOVEMENT_SIZE);
      }
      if (moviments[0] === "ré") {
        setRotate(180);
        setMarginRight((oldValue) => oldValue + MOVEMENT_SIZE);
      }
      if (moviments[0] === "direita") {
        setRotate(90);
        setMarginTop((oldValue) => oldValue + MOVEMENT_SIZE);
      }
      if (moviments[0] === "esquerda") {
        setRotate(270);
        setMarginBottom((oldValue) => oldValue + MOVEMENT_SIZE);
      }
      moviments.shift();
      executeMoviments(moviments);
    }, 1500);
  }

  function equalsCheck(a: string[], b: string[]) {
    return JSON.stringify(a) === JSON.stringify(b);
  }

  const messageListener = (message: any) => {
    const moviments = message.map((moviment: any) => moviment.movimento);
    if (!equalsCheck(moviments, movimentos)) {
      resetMoviments();
      setMovimentos(moviments);
      executeMoviments(moviments);
    }
  };

  useEffect(() => {
    const newSocket = io("http://localhost:5000");

    newSocket?.on("movimentos", messageListener);
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  return (
    <Container>
      <Street>
        <Car
          marginBottom={marginBottom}
          marginLeft={marginLeft}
          marginRight={marginRight}
          marginTop={marginTop}
          rotate={rotate}
        />
      </Street>
    </Container>
  );
}

export default Home;
