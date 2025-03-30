{
  description = "Nix Slicc Dev Env";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
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
            bison libgcc stdenv cmake clang-tools clang lldb flex cppcheck conan
          ];
          shellHook = ''
            LD_LIBRARY_PATH='${pkgs.lib.makeLibraryPath [ pkgs.stdenv.cc.cc ]}'
            PATH="${pkgs.clang-tools}/bin:$PATH"
          '';
          LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [ pkgs.stdenv.cc.cc ];
        };
      });
    };
}
