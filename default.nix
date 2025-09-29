{
  pkgs ? import <nixpkgs>,
}:
pkgs.stdenv.mkDerivation rec {
  pname = "dino";
  name = pname;
  src = ./.;

  buildInputs = with pkgs; [
    gcc
    gnumake
    ncurses
  ];

  nativeBuildInputs = [ pkgs.gnumake ];

  buildPhase = ''
    make dino
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp dino $out/bin/
  '';
}
