{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs =
    {
      nixpkgs,
      flake-utils,
      ...
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      rec {
        packages = flake-utils.lib.flattenTree {
          dino = pkgs.callPackage ./default.nix { };
        };
        defaultPackage = packages.dino;
        devShell = pkgs.mkShell {
          name = "dinoGame";
          packages = with pkgs; [
            gcc
            gnumake
            ncurses
          ];
        };
      }
    );
}
