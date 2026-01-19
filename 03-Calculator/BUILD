cc_library(
    name = "cal_lib",
    srcs = ["cal.cpp"],
    hdrs = ["cal.hpp"],
)

cc_binary(
    name = "calculator",
    srcs = ["main.cpp"],
    deps = ["//:cal_lib"],
)