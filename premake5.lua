newoption {
   trigger     = "location",
   value       = "./",
   description = "Where to generate the project.",
}

if not _OPTIONS["location"] then
   _OPTIONS["location"] = "./"
end

include(_OPTIONS["location"] .. "conanbuildinfo.premake.lua")

workspace("client_server")
	location(_OPTIONS["location"])
	conan_basic_setup()

	project("client")
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		targetdir = "bin/%{cfg.buildcfg}"

		files{
			"src/client/**",
		}

		includedirs{
			"src/client",
			"src/shared"
		}

		defines{"_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS"}

		filter "configurations:Debug"
			defines { "DEBUG" }
			symbols "On"

		filter "configurations:Release"
			defines { "NDEBUG" }
			optimize "On"

	project("server")
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		targetdir = "bin/%{cfg.buildcfg}"

		files{
			"src/server/**",
		}

		includedirs{
			"src/server",
			"src/shared"
		}

		defines{"_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS"}

		filter "configurations:Debug"
			defines { "DEBUG" }
			symbols "On"

		filter "configurations:Release"
			defines { "NDEBUG" }
			optimize "On"