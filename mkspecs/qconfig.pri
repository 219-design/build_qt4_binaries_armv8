#configuration
CONFIG +=  no_mocdepend release stl qt_no_framework
QT_ARCH = arm
QT_EDITION = OpenSource
QT_CONFIG +=  accessibility minimal-config small-config medium-config large-config full-config embedded reduce_exports ipv6 clock-gettime clock-monotonic mremap getaddrinfo ipv6ifname getifaddrs inotify png gif freetype zlib svg release

#versioning
QT_VERSION = 4.4.3
QT_MAJOR_VERSION = 4
QT_MINOR_VERSION = 4
QT_PATCH_VERSION = 3

#namespaces
QT_LIBINFIX = 
QT_NAMESPACE = 

QMAKE_RPATHDIR += "/opt/legacy_qt/armv8_rpi/lib"
