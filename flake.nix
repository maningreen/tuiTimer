{
  description = "An environment for c development";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self , nixpkgs ,... }: let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in {
    devShells.${system}.default = pkgs.callPackage ./shell.nix {inherit pkgs;};
    packages.${system}.default = pkgs.callPackage ./default.nix {inherit pkgs;};
  };
}
