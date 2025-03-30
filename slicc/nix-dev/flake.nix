{
  description = "Nix Slicc Dev Env";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    # pkgs-dotnet-sdk_8_0_pinned.url = "https://github.com/NixOS/nixpkgs/archive/ab7b6889ae9d484eed2876868209e33eb262511d.tar.gz";
  };

  outputs = { self, nixpkgs }:
    let
      supportedSystems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
      forEachSupportedSystem = f: nixpkgs.lib.genAttrs supportedSystems (system: f {
        pkgs = import nixpkgs { 
          inherit system; 
          overlays = [ self.overlays.default ]; 
          config = {};
        };
      });

    in
    {
      overlays.default = final: prev: rec {
        nodejs = prev.nodejs;
        yarn = (prev.yarn.override { inherit nodejs; });
      };


      devShells = forEachSupportedSystem ({ pkgs }: {
        default = pkgs.mkShell {
          packages = with pkgs; [ 
            bison cmake clang flex clang-tools cppcheck
          ];
          shellHook = ''
          '';
        };
      });
    };
}
