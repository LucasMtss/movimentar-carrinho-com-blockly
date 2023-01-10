import styled from "styled-components";

interface IProps {
  rotate: number;
  marginTop: number;
  marginRight: number;
  marginLeft: number;
  marginBottom: number;
}

export const ImageCar = styled.img<IProps>`
  transform: ${(props) => `rotate(${props.rotate}deg)`};
  margin-left: ${(props) => `${props.marginLeft}px`};
  margin-right: ${(props) => `${props.marginRight}px`};
  margin-top: ${(props) => `${props.marginTop}px`};
  margin-bottom: ${(props) => `${props.marginBottom}px`};
  transition: all 500ms ease-in-out;
`;
