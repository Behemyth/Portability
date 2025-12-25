/// Portability Library - Aggregate Module
/// Import this module to get all portability features at once.
/// For selective imports, use the individual modules:
///   - synodic.portability.core         (concepts and base classes)
///   - synodic.portability.platform     (OS detection)
///   - synodic.portability.compiler     (compiler detection + feature traits)
///   - synodic.portability.architecture (CPU architecture detection)
///   - synodic.portability.build        (debug/release, sanitizers)
export module synodic.portability;

export import synodic.portability.core;
export import synodic.portability.platform;
export import synodic.portability.compiler;
export import synodic.portability.architecture;
export import synodic.portability.build;
