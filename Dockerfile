FROM evenzeppa/42env:latest AS builder

WORKDIR /root
COPY . .

RUN cmake -B build && \
		cmake --build build

FROM evenzeppa/42env:latest AS app

WORKDIR /root/ft_irc

RUN apt-get update && apt-get install -y tini && apt-get clean

COPY --from=builder /root/build/ircserv ./ircserv

ENTRYPOINT ["/usr/bin/tini", "--"]
CMD ["./ircserv", "6667", "1234"]
