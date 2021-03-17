void files_secured()
{
	FILE* f;
	string s2 = "123456789012345678901234567890";

	char s[10] = "qwertyiop";
	char s1[31];
	fopen_s(&f, "d:\\test.txt", "w+");
	cout << fwrite(s2.c_str(), 1, s2.length(), f) << endl;
	fclose(f);

	fopen_s(&f, "d:\\test.txt", "r");
	int n = fread(s1, 1, sizeof(s1) - 1, f);
	cout << n << endl;
	s1[n] = '\0';
	cout << s1 << endl;
	fclose(f);

	return ;
}