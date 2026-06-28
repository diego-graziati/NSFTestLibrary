# ==========================================
# STAGE 1: Base di sviluppo e Test (Leggera)
# ==========================================
FROM ubuntu:24.04 AS base_test

# Evita interazioni bloccanti durante l'installazione
ENV DEBIAN_FRONTEND=noninteractive

# Installa i tool minimi per compilare e testare
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    cppcheck \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
COPY . .

# Comando di default per lo stage di test
CMD ["sh", "-c", "cmake -B build_docker -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON -DENABLE_SANITIZERS=ON && cmake --build build_docker && cd build_docker && ctest --output-on-failure"]


# ==========================================
# STAGE 2: Generazione Documentazione (Completa)
# ==========================================
FROM base_test AS doc_builder

# Installa Doxygen e Graphviz (necessario per i grafici DOT e SVG che hai configurato)
RUN apt-get update && apt-get install -y \
    doxygen \
    graphviz \
    && rm -rf /var/lib/apt/lists/*

# Comando di default per lo stage di documentazione
CMD ["sh", "-c", "cmake -B build_docker -DBUILD_DOCS=ON && cmake --build build_docker --target api_docs && cmake --build build_docker --target complete_docs"]