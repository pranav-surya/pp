def gcd(a, b)
	a = a.abs
	b = b.abs
	return 0 if a == 0 && b == 0
	while(b != 0)
		a, b = b, a % b
	end
	a
end

def rotate(array, x)
	def reverse(arr, l, r)
		while (l < r)
			t = arr[l]
			arr[l] = arr[r]
			arr[r] = t
			l += 1
			r -= 1
		end
	end
	reverse(array, 0, x-1)
	reverse(array, x, array.size-1)
	reverse(array, 0, array.size-1)
end

# File.open("/Users/prsurya/Desktop/pp/10_million_numbers.txt", "w") do |f|
#     "1234567890".split('').repeated_permutation(7).each do |digits|
#     	number = digits.join
#     	f.puts(number) if number[0] != "0"
#     end
# end

def compress_numbers
	total_bits = 1000
	integer_size = 64
	buffer_size = (total_bits / integer_size) + 1
	mask = integer_size - 1
	buffer = Array.new(buffer_size, 0)
	input = File.foreach("/Users/prsurya/Desktop/pp/10_million_numbers.txt", mode: "r", chomp: true) do |line|
		number = line.to_i
		integer_bit_pos = number & mask
		buffer_index = number / integer_size
		buffer[buffer_index] = buffer[buffer_index] | (1 << integer_bit_pos)
	end
	File.open("/Users/prsurya/Desktop/pp/10_million_numbers_compressed.txt", mode: "w") do |file|
		number = 0
	    while (number < total_bits)
	    	integer_bit_pos = number & mask
	    	buffer_index = number / integer_size
	    	if ((buffer[buffer_index] & (1 << integer_bit_pos)) != 0)
	    		file.puts(number)
	    	end
	    	number += 1
	    end
	end
end

def compress_numbers2
	numbers = []
	input = File.foreach("/Users/prsurya/Desktop/pp/10_million_numbers.txt", mode: "r", chomp: true) do |line|
		numbers << line.to_i
	end
	numbers.sort!
	File.open("/Users/prsurya/Desktop/pp/10_million_numbers_compressed.txt", mode: "w") do |file|
		numbers.each do |i|
			file.puts(i)
		end
	end
end
