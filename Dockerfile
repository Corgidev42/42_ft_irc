FROM evenzeppa/42env:latest AS builder

WORKDIR /root
COPY . .

WORKDIR /root/BNFParserLib
RUN mkdir build && \
	cd build && \
	cmake .. && \
	cmake -DCMAKE_INSTALL_PREFIX=/usr/local .. && \
	make install

WORKDIR /root/spdlog
RUN mkdir build && \
	cd build && \
	cmake .. && \
	cmake --build . && \
	cp libspdlog.a /usr/local/libspdlog.a

WORKDIR /root
RUN make

FROM evenzeppa/42env:latest AS app

WORKDIR /root/ft_irc

RUN apt-get update && apt-get install -y tini && apt-get clean

COPY --from=builder /root/ft_irc ./ft_irc

ENTRYPOINT ["/usr/bin/tini", "--"]
CMD ["./ft_irc", "6667", "1234"]
