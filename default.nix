{pkgs ? import <nixpkgs> {}, ...}: let 
  excecutable = "out";
in pkgs.stdenv.mkDerivation {
  name = excecutable;
  description = "An application with ncurses";
  src = ./.; 
  buildInputs = with pkgs; [
    ncurses
  ];

  buildPhase = ''
mkdir -p build
make -j3
'';

  installPhase = ''
mkdir -p $out/bin
install -t $out/bin build/${excecutable}
  '';
}
