/*
 * Cezary Pietrzak, 160667
 * Martyna Kulbacka, 160515
 */

unsigned int convert_endian(unsigned int bytes) {
	return ((bytes>>24)&0xff) | ((bytes<<8)&0xff0000) | ((bytes>>8)&0xff00) | ((bytes<<24)&0xff000000);
}