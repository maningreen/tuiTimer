{
  description = "An environment for c development";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self , nixpkgs ,... }: let
    system = "x86_64-linux";
    supportedSystems = [
      "x86_64-linux"
      "x86_64-darwin"
      "aarch64-linux"
      "aarch64-darwin"
    ];

    mapSystems = nixpkgs.lib.genAttrs supportedSystems;
  in {

    devShells = mapSystems (
      system : let 
        pkgs = nixpkgs.legacyPackages.${system};
      in pkgs.callPackage ./shell.nix {inherit pkgs;});

    defaultPackage = mapSystems (
      system : let 
        pkgs = nixpkgs.legacyPackages.${system};
      in pkgs.callPackage ./default.nix {inherit pkgs;});
  };
}
