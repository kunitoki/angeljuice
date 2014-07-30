#pragma extension "core"
#pragma debug "off"


//=======================================================================
void main()
{    
    // run tests
    test_string();
    test_time();

    // SystemStats
    assert(SystemStats.getOperatingSystemType() == SystemStats::Linux);
    assert(SystemStats.getOperatingSystemName() == "Linux");
    
    // BigInteger
    //println(BigInteger(122312345).toString(16));
    
    // Random
    Random r(1234);
    assert(r.nextInt() == 474780142);
    
    // Array<T>
    //String test("123");
    //Array<String> a(1);
    //a[0] = "1456";
    //a[0] = test;
    //println(a[0]);
}


//=======================================================================

void test_string()
{
	String first("testing our first string");

	String second("the second must be last string ");
	second.append(first, 4);

	String third;
	
	String utf8("àòùì'122123");

	String a("123"), b("456");
	
	String sll;

    assert("1234" == String(1234));
    assert("0" == String(false));
    assert("1" == String(true));
    assert("3.14" == String(3.14));
	assert(first[0] == "t");
	assert(first.hashCode() == 1787091941);
	assert(int(first.hashCode64()) == 126803343);
	assert(first.length() == 24);
	assert(second == "the second must be last string test");
	assert(sll == String::empty);
	assert(first != String::empty);
	assert(first.isEmpty() == false);
	assert(first.isNotEmpty() == true);
	assert(third.isEmpty() == true);
	assert(third.isNotEmpty() == false);
	assert("asdfQWER".equalsIgnoreCase("ASDFqwer"));
	assert("asdfQWER".equalsIgnoreCase("qwerASDF") == false);
	assert("123".compare("123") == 0);
	assert("123".compare("321") < 0);
	assert("321".compare("123") > 0);
	assert("Abc".compareIgnoreCase("aBC") == 0);
	assert("Abc".compareIgnoreCase("CBa") < 0);
	assert("cbA".compareIgnoreCase("aBC") > 0);
	assert("2".compareNatural("2") == 0);
	assert("2".compareNatural("20") < 0);
	assert("20".compareNatural("2") > 0);
	assert("2013".startsWith("2"));
	assert("2013".startsWith("0") == false);
	assert("2013".startsWithChar('2'));
	assert("abc".startsWithIgnoreCase("A"));
	assert("abc".startsWithIgnoreCase("a"));
	assert("2013".endsWith("3"));
	assert("2013".endsWith("2") == false);
	assert("2013".endsWithChar('3'));
	assert("abc".endsWithIgnoreCase("C"));
	assert("abc".endsWithIgnoreCase("c"));
	assert("abc".contains("ab"));
	assert("abc".contains("c"));
	assert("abc".contains("z") == false);
	assert("2013".containsChar('2'));
	assert("abc".containsIgnoreCase("AB"));
	assert("abc".containsIgnoreCase("C"));
	assert("abc".containsIgnoreCase("Z") == false);
	assert(first.containsWholeWord("first"));
	assert(first.containsWholeWord("testin") == false);
	assert(first.containsWholeWordIgnoreCase("FIRST"));
	assert(first.containsWholeWordIgnoreCase("teSTin") == false);
	assert(first.containsAnyOf("s"));
	assert(first.containsAnyOf("q") == false);
	assert("12345".containsOnly("54321"));
	assert("12345".containsOnly("1234") == false);
	assert("  12 34 5".containsNonWhitespaceChars());
	assert(" \t\r\n".containsNonWhitespaceChars() == false);
	assert("12345".matchesWildcard("12*45", true));
	assert("12345".matchesWildcard("12*34", true) == false);
	assert(first.indexOfWholeWord("string") == 18);
	assert(first.indexOfWholeWordIgnoreCase("STRing") == 18);
	assert("123425".lastIndexOfChar('2') == 4);
	assert("1253425".lastIndexOf("25") == 5);
	assert("abcABCabC".lastIndexOf("abc") == 0);
	assert("abcABC".lastIndexOfIgnoreCase("aBc") == 3);
	assert("abcABC".lastIndexOfAnyOf("aBc", true) == 5);
	assert(" 1234 ".trim() == "1234");
    assert(" 1234 ".trimStart() == "1234 ");
    assert(" 1234 ".trimEnd() == " 1234");
	assert("abcABC".toUpperCase() == "ABCABC");
	assert("abcABC".toLowerCase() == "abcabc");
	assert("123abc123".replaceSection(0, 3, "456") == "456abc123");
	assert("123abc123".replaceSection(6, 3, "456") == "123abc456");
	assert("123abc123".replace("123", "456") == "456abc456");
	assert("123abc123".replace("123ABC", "321ABC", true) == "321ABC123");
	assert("123abc123".replace("abc", "ABC", false) == "123ABC123");
	assert("123abc123".replaceCharacter('1', '9') == "923abc923");
	assert("123abc123".replaceCharacters("12", "45") == "453abc453");
	assert("123abc123".retainCharacters("a3") == "3a3");
	assert("123abc123".removeCharacters("a3") == "12bc12");
	assert("121abc121".initialSectionContainingOnly("12") == "121");
	assert("123abc123".initialSectionNotContaining("abc") == "123");
	assert("\"abc\"".isQuotedString());
	assert("'abc'".isQuotedString());
	assert("abc".isQuotedString() == false);
	assert("\"abc".isQuotedString());
	assert("abc\"".isQuotedString() == false);
	assert("'abc".isQuotedString());
	assert("abc'".isQuotedString() == false);
	assert("'abc\"".isQuotedString());
	assert("\"abc'".isQuotedString());
	assert("\"abc\"".unquoted() == "abc");
	assert("abc".quoted("'") == "'abc'");
	assert("abc".quoted() == "\"abc\"");
	assert("ab1".getLastCharacter() == '1');
	assert("abcdefg".substring(3) == "defg");
	assert("abcdefg".substring(3,4) == "d");
	assert("abcdefg".dropLastCharacters(2) == "abcde");
	assert("abcdefg".getLastCharacters(3) == "efg");
	assert("abcdefg".fromFirstOccurrenceOf("de", true, true) == "defg");
	assert("abcdefg".fromFirstOccurrenceOf("de", false, true) == "fg");
	assert("abcdefg".fromLastOccurrenceOf("de", true, true) == "defg");
	assert("abcdefg".fromLastOccurrenceOf("de", false, true) == "fg");
	assert("abcdefg".upToFirstOccurrenceOf("de", true, true) == "abcde");
	assert("abcdefg".upToFirstOccurrenceOf("de", false, true) == "abc");
	assert("abcdefg".upToLastOccurrenceOf("de", true, true) == "abcde");
	assert("abcdefg".upToLastOccurrenceOf("de", false, true) == "abc");
	assert("9001".getIntValue() == 9001);
	assert("1a2b3".getTrailingIntValue() == 3);
	assert("9223372036854775800".getLargeIntValue() == 9223372036854775800);
	assert("1.0".getFloatValue() == float(1.0));
	assert("1.0000000000001".getDoubleValue() == double(1.0000000000001));
	assert("100".getHexValue32() == 256);
	assert("100".getHexValue64() == int(256));
	assert(a == "123");
	assert(b == "456");
	a.swapWith(b);
	assert(a == "456");
	assert(b == "123");

	sll << int8(-1);
	assert(sll == "-1");
	sll << uint8(1);
	assert(sll == "-11");
	sll << int16(-1);
	assert(sll == "-11-1");
	sll << uint16(1);
	assert(sll == "-11-11");
	sll << int32(-1);
	assert(sll == "-11-11-1");
	sll << uint32(1);
	assert(sll == "-11-11-11");
	sll << int64(-1);
	assert(sll == "-11-11-11-1");
	sll << uint64(1);
	assert(sll == "-11-11-11-11");
	sll << float(3.14);
	assert(sll == "-11-11-11-113.14");
	sll << "-0001";
	assert(sll == "-11-11-11-113.14-0001");
	// TODO - does not work
	//sll << double(1.0000000000001);
	//assert(sll == "-113.141.0000000000001");
	
}


//=======================================================================

void test_time()
{
    Time time(1000002);

    assert(time.toMilliseconds() == 1000002);
    assert(time.getYear() == 1970);
    assert(time.getMonth() == 0);
    assert(time.getMonthName(true) == "Jan");
    assert(time.getMonthName(false) == "January");
    assert(time.getDayOfMonth() == 1);
    assert(time.getDayOfYear() == -1);
    assert(time.getDayOfWeek() == 4);
    assert(time.getWeekdayName(true) == "Thu");
    assert(time.getWeekdayName(false) == "Thursday");
    assert(time.getHours() == 1);
    assert(time.getMinutes() == 16);
    assert(time.getSeconds() == 40);
    assert(time.isAfternoon() == false);
    assert(time.getHoursInAmPmFormat() == 1);
    assert(time.getMilliseconds() == 2);
    assert(time.isDaylightSavingTime() == true);
    assert(time.getTimeZone() == "CES");
    assert(time.formatted("%Y%A%m") == "1970Thursday01");
    assert(time.toString(true, true, true, true) == "1 Jan 1970 1:16:40");
    
    assert(Time::getMonthName(10, true) == "Nov");
    assert(Time::getMonthName(10, false) == "November");
}
