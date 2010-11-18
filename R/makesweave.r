makesweave = function (file, robust=TRUE)
{	status = try (Sweave (file) )
	if (robust)
	{	str = if (class (status) == "try-error") "1\n" else "0\n"
		write (str, "/tmp/makesweavestatus")
	}
}

