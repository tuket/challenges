const std = @import("std");
const io = std.io;
const debug = std.debug;
const warn = debug.warn;
const TypeId = @import("builtin").TypeId;

pub fn read(comptime T : type) !T {
    if(@typeId(T) == TypeId.Int) {
        var stdin = try io.getStdIn();
        var stdin_stream = stdin.inStream();
        var x : T = 0;
        var byte = try stdin_stream.stream.readByte();
        while('0' <= byte and byte <= '9') {
            x *= 10;
            x += @intCast(T, byte - '0');
            byte = try stdin_stream.stream.readByte();
        }
        return x;
    }
}

pub fn main() !void {
    const stdoutFile = try std.io.getStdOut();
    const stdout = &stdoutFile.outStream().stream;
    const nn = try read(i64);
    var kk: i64 = 1;
    while (kk <= nn) : (kk += 1) {
        const n = try read(u128);
        const k = try read(u128);
        const mask = (@intCast(u128, 1) << @intCast(u7, n)) - 1;
        if((k & mask) != mask) {
            try stdout.print("Case #{}: OFF\n", kk);
        }
        else {
            try stdout.print("Case #{}: ON\n", kk);
        }
    }
}