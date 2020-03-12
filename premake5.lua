workspace "minimidi"
  characterset ("MBCS")
  configurations { "Debug", "Release" }
  startproject "app.minimidi"
  location ".build/projects"
  targetdir ".build/bin/%{cfg.buildcfg}"
  debugdir "bin"
  language "C++"
  architecture "x64"

  linkoptions {
  }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "Full"
    optimize "Off"
    targetsuffix "-d"

  filter "configurations:Release"
    defines { "RELEASE", "NDEBUG" }
    symbols "Off"
    optimize "Size"

project "app.minimidi"
  kind "ConsoleApp"
  language "C++"

  includedirs { "externals/" }

  files { "source/app.minimidi/**.h", "source/app.minimidi/**.c", "source/app.minimidi/**.cpp" }
