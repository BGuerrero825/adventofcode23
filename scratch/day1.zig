const std = @import("std");

pub fn main() !void {
    const allocator = std.heap.page_allocator;

    // Take user input
    const stdin = std.io.getStdIn().reader();
    const userInput = try std.io.readUntilDelimiter(stdin, '\n', allocator);

    // Filter digits from the user input
    var digits: [0]u8 = undefined;
    var digitCount: usize = 0;

    for (userInput) |char| {
        if (char >= '0' and char <= '9') {
            if (digitCount == digits.len) {
                // Resize the array if needed
                _ = std.mem.arrayAppend(&allocator, &digits, 10);
            }
            digits[digitCount] = char;
            digitCount += 1;
        }
    }

    // Output the extracted digits
    std.debug.print("Digits found: {}\n", .{std.mem.sliceToLen(digits[0..], digitCount)});
}
