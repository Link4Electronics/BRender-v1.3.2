#
#
$width = 16;
$ofset = 0;
open(IN,$ARGV[0]);
binmode(IN);

print "/*\n * Generated by dumpc.pl\n */\n";

while($len = read(IN,$data,$width)) {
	printf "\t/* %04x */ ",$offset ;
	for($i = 0; $i < $len; $i++) {
		printf "0x%02x,", ord(substr($data,$i,1)) ;
	}
	printf "\n";

	$offset += $width;
}
