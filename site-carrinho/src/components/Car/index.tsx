import React from "react";
import { ImageCar } from "./style";
import car from "../../assets/car-image.png";

interface IProps {
  rotate: number;
  marginTop: number;
  marginRight: number;
  marginLeft: number;
  marginBottom: number;
}

function Car({
  rotate,
  marginBottom,
  marginLeft,
  marginRight,
  marginTop,
}: IProps) {
  return (
    <ImageCar
      marginBottom={marginBottom}
      marginLeft={marginLeft}
      marginRight={marginRight}
      marginTop={marginTop}
      rotate={rotate}
      src={car}
    />
  );
}

export default Car;
