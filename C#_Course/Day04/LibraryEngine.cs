namespace Day04
{
    public class LibraryEngine
    {
        public static void ProcessBooksWithFunc(List<Book> bList, Func<Book, string> fPtr)
        {
            foreach (Book B in bList)
            {
                Console.WriteLine(fPtr?.Invoke(B) ?? "Error");
            }
        }

        public static void ProcessBooks(List<Book> bList, GeneralDel<Book, string> del)
        {
            foreach (Book B in bList)
            {
                Console.WriteLine(del?.Invoke(B) ?? "Error");
            }
        }
    }
}
