{pkgs ? import <nixpkgs> {}, ...}: pkgs.mkShell {
  packages = with pkgs; [
    gnumake
    gcc
    ncurses
  ];

  shellHook = ''
    echo "Happy developing!"
  '';
}
