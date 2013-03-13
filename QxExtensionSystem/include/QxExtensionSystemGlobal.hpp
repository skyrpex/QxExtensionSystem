#pragma once

#include <qglobal.h>

#if defined(QXEXTENSIONSYSTEM_LIBRARY)
#  define QXEXTENSIONSYSTEM_EXPORT Q_DECL_EXPORT
#else
#  define QXEXTENSIONSYSTEM_EXPORT Q_DECL_IMPORT
#endif
