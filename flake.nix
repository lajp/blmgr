{
  description = "blmgr - A backlight manager";

  # Nixpkgs / NixOS version to use.
  inputs = {
    nixpkgs.url = "nixpkgs/nixos-21.05";
    systems.url = "github:nix-systems/default";
  };

  outputs = {
    self,
    nixpkgs,
    systems,
  }: let
    eachSystem = nixpkgs.lib.genAttrs (import systems);
  in {
    packages = eachSystem (
      system: let
        pkgs = nixpkgs.legacyPackages.${system};
        blmgr = pkgs.stdenv.mkDerivation {
          nativeBuildInputs = [pkgs.clang];
          name = "blmgr";
          version = "0.1.0";
          src = ./.;

          buildPhase = ''
            make
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp blmgr $out/bin
          '';
        };
      in {
        inherit blmgr;
        default = blmgr;
      }
    );
  };
}
