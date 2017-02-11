QT += qml quick bluetooth widgets

CONFIG += c++11

SOURCES += main.cpp \
    blecontroller.cpp \
    bluetoothdevicedataobject.cpp \
    messagehelper.cpp \
    chargermodel.cpp \
    filebrowserdata.cpp \
    filehelper.cpp \
    programparser.cpp \
    programstep.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    blecontroller.h \
    bluetoothdevicedataobject.h \
    messagehelper.h \
    boost/config/abi/borland_prefix.hpp \
    boost/config/abi/borland_suffix.hpp \
    boost/config/abi/msvc_prefix.hpp \
    boost/config/abi/msvc_suffix.hpp \
    boost/config/compiler/borland.hpp \
    boost/config/compiler/clang.hpp \
    boost/config/compiler/codegear.hpp \
    boost/config/compiler/comeau.hpp \
    boost/config/compiler/common_edg.hpp \
    boost/config/compiler/compaq_cxx.hpp \
    boost/config/compiler/cray.hpp \
    boost/config/compiler/digitalmars.hpp \
    boost/config/compiler/gcc.hpp \
    boost/config/compiler/gcc_xml.hpp \
    boost/config/compiler/greenhills.hpp \
    boost/config/compiler/hp_acc.hpp \
    boost/config/compiler/intel.hpp \
    boost/config/compiler/kai.hpp \
    boost/config/compiler/metrowerks.hpp \
    boost/config/compiler/mpw.hpp \
    boost/config/compiler/nvcc.hpp \
    boost/config/compiler/pathscale.hpp \
    boost/config/compiler/pgi.hpp \
    boost/config/compiler/sgi_mipspro.hpp \
    boost/config/compiler/sunpro_cc.hpp \
    boost/config/compiler/vacpp.hpp \
    boost/config/compiler/visualc.hpp \
    boost/config/compiler/xlcpp.hpp \
    boost/config/no_tr1/cmath.hpp \
    boost/config/no_tr1/complex.hpp \
    boost/config/no_tr1/functional.hpp \
    boost/config/no_tr1/memory.hpp \
    boost/config/no_tr1/utility.hpp \
    boost/config/platform/aix.hpp \
    boost/config/platform/amigaos.hpp \
    boost/config/platform/beos.hpp \
    boost/config/platform/bsd.hpp \
    boost/config/platform/cloudabi.hpp \
    boost/config/platform/cray.hpp \
    boost/config/platform/cygwin.hpp \
    boost/config/platform/haiku.hpp \
    boost/config/platform/hpux.hpp \
    boost/config/platform/irix.hpp \
    boost/config/platform/linux.hpp \
    boost/config/platform/macos.hpp \
    boost/config/platform/qnxnto.hpp \
    boost/config/platform/solaris.hpp \
    boost/config/platform/symbian.hpp \
    boost/config/platform/vms.hpp \
    boost/config/platform/vxworks.hpp \
    boost/config/platform/win32.hpp \
    boost/config/stdlib/dinkumware.hpp \
    boost/config/stdlib/libcomo.hpp \
    boost/config/stdlib/libcpp.hpp \
    boost/config/stdlib/libstdcpp3.hpp \
    boost/config/stdlib/modena.hpp \
    boost/config/stdlib/msl.hpp \
    boost/config/stdlib/roguewave.hpp \
    boost/config/stdlib/sgi.hpp \
    boost/config/stdlib/stlport.hpp \
    boost/config/stdlib/vacpp.hpp \
    boost/config/abi_prefix.hpp \
    boost/config/abi_suffix.hpp \
    boost/config/auto_link.hpp \
    boost/config/posix_features.hpp \
    boost/config/requires_threads.hpp \
    boost/config/select_compiler_config.hpp \
    boost/config/select_platform_config.hpp \
    boost/config/select_stdlib_config.hpp \
    boost/config/suffix.hpp \
    boost/config/user.hpp \
    boost/config/warning_disable.hpp \
    boost/config.hpp \
    boost/crc.hpp \
    boost/cstdint.hpp \
    boost/integer.hpp \
    boost/integer_fwd.hpp \
    boost/integer_traits.hpp \
    boost/limits.hpp \
    boost/static_assert.hpp \
    boost/detail/winapi/detail/cast_ptr.hpp \
    boost/detail/winapi/access_rights.hpp \
    boost/detail/winapi/apc.hpp \
    boost/detail/winapi/basic_types.hpp \
    boost/detail/winapi/character_code_conversion.hpp \
    boost/detail/winapi/condition_variable.hpp \
    boost/detail/winapi/config.hpp \
    boost/detail/winapi/critical_section.hpp \
    boost/detail/winapi/crypt.hpp \
    boost/detail/winapi/dbghelp.hpp \
    boost/detail/winapi/directory_management.hpp \
    boost/detail/winapi/dll.hpp \
    boost/detail/winapi/environment.hpp \
    boost/detail/winapi/error_codes.hpp \
    boost/detail/winapi/error_handling.hpp \
    boost/detail/winapi/event.hpp \
    boost/detail/winapi/file_management.hpp \
    boost/detail/winapi/file_mapping.hpp \
    boost/detail/winapi/get_current_process.hpp \
    boost/detail/winapi/get_current_process_id.hpp \
    boost/detail/winapi/get_current_thread.hpp \
    boost/detail/winapi/get_current_thread_id.hpp \
    boost/detail/winapi/get_last_error.hpp \
    boost/detail/winapi/get_process_times.hpp \
    boost/detail/winapi/get_system_directory.hpp \
    boost/detail/winapi/get_thread_times.hpp \
    boost/detail/winapi/GetCurrentProcess.hpp \
    boost/detail/winapi/GetCurrentThread.hpp \
    boost/detail/winapi/GetLastError.hpp \
    boost/detail/winapi/GetProcessTimes.hpp \
    boost/detail/winapi/GetThreadTimes.hpp \
    boost/detail/winapi/handle_info.hpp \
    boost/detail/winapi/handles.hpp \
    boost/detail/winapi/heap_memory.hpp \
    boost/detail/winapi/init_once.hpp \
    boost/detail/winapi/jobs.hpp \
    boost/detail/winapi/limits.hpp \
    boost/detail/winapi/local_memory.hpp \
    boost/detail/winapi/memory.hpp \
    boost/detail/winapi/mutex.hpp \
    boost/detail/winapi/overlapped.hpp \
    boost/detail/winapi/page_protection_flags.hpp \
    boost/detail/winapi/pipes.hpp \
    boost/detail/winapi/priority_class.hpp \
    boost/detail/winapi/process.hpp \
    boost/detail/winapi/security.hpp \
    boost/detail/winapi/semaphore.hpp \
    boost/detail/winapi/shell.hpp \
    boost/detail/winapi/show_window.hpp \
    boost/detail/winapi/srw_lock.hpp \
    boost/detail/winapi/synchronization.hpp \
    boost/detail/winapi/system.hpp \
    boost/detail/winapi/thread.hpp \
    boost/detail/winapi/thread_pool.hpp \
    boost/detail/winapi/time.hpp \
    boost/detail/winapi/timers.hpp \
    boost/detail/winapi/tls.hpp \
    boost/detail/winapi/wait.hpp \
    boost/detail/winapi/waitable_timer.hpp \
    boost/detail/algorithm.hpp \
    boost/detail/allocator_utilities.hpp \
    boost/detail/atomic_count.hpp \
    boost/detail/atomic_redef_macros.hpp \
    boost/detail/atomic_undef_macros.hpp \
    boost/detail/basic_pointerbuf.hpp \
    boost/detail/binary_search.hpp \
    boost/detail/bitmask.hpp \
    boost/detail/call_traits.hpp \
    boost/detail/catch_exceptions.hpp \
    boost/detail/compressed_pair.hpp \
    boost/detail/container_fwd.hpp \
    boost/detail/dynamic_bitset.hpp \
    boost/detail/endian.hpp \
    boost/detail/fenv.hpp \
    boost/detail/has_default_constructor.hpp \
    boost/detail/identifier.hpp \
    boost/detail/indirect_traits.hpp \
    boost/detail/interlocked.hpp \
    boost/detail/is_incrementable.hpp \
    boost/detail/is_sorted.hpp \
    boost/detail/is_xxx.hpp \
    boost/detail/iterator.hpp \
    boost/detail/lcast_precision.hpp \
    boost/detail/lightweight_main.hpp \
    boost/detail/lightweight_mutex.hpp \
    boost/detail/lightweight_test.hpp \
    boost/detail/lightweight_test_report.hpp \
    boost/detail/lightweight_thread.hpp \
    boost/detail/named_template_params.hpp \
    boost/detail/no_exceptions_support.hpp \
    boost/detail/numeric_traits.hpp \
    boost/detail/ob_compressed_pair.hpp \
    boost/detail/quick_allocator.hpp \
    boost/detail/reference_content.hpp \
    boost/detail/scoped_enum_emulation.hpp \
    boost/detail/select_type.hpp \
    boost/detail/sp_typeinfo.hpp \
    boost/detail/templated_streams.hpp \
    boost/detail/utf8_codecvt_facet.hpp \
    boost/detail/utf8_codecvt_facet.ipp \
    boost/detail/workaround.hpp \
    chargermodel.h \
    callbackitem.h \
    filebrowserdata.h \
    filehelper.h \
    programparser.h \
    programstep.h

#unix|win32: LIBS += -lQt5Bluetooth

DISTFILES += \
    Libs/qt-crc32-master/.gitignore \
    Libs/qt-crc32-master/LICENSE \
    Libs/qt-crc32-master/README.md
