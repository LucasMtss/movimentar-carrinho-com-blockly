import styled from "styled-components";
import bg from "../../assets/street-image.png";

export const Container = styled.main`
  width: 100vw;
  display: flex;
  justify-content: center;
  align-items: center;
  min-height: 100vh;
  background-color: #1d1d1d;
`;

export const Street = styled.div`
  width: 1400px;
  height: 750px;
  background-image: url(${bg});
  background-size: contain;
  display: flex;
  align-items: center;
  overflow: hidden;
`;
