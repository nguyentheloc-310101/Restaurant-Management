
		}
		else if (str == "UNLIMITED_VOID") // UNLIMITED_VOID
		{
			r->UNLIMITED_VOID();
		}
		else if (str == "DOMAIN_EXPANSION") // DOMAIN_EXPANSION
		{
			r->DOMAIN_EXPANSION();
		}
		else // LIGHT <NUM>
		{
			ss >> num;
			r->LIGHT(stoi(num));
		}
	}
}
