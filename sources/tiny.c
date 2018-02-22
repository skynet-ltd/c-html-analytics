#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tidy/buffio.h>

/* Traverse the document tree */
void dumpNode(TidyDoc doc, TidyNode tnod, int indent)
{
    TidyNode child = tidyGetChild(tnod);
    for (; child; child = tidyGetNext(child))
    {
        ctmbstr name = tidyNodeGetName(child);
        if (name)
        {
            printf("%*.*s%s\n", indent, (int)strlen(name), "", name);
        }
        else
        {
            /* if it doesn't have a name, then it's probably text, cdata, etc... */
            TidyBuffer buf;
            tidyBufInit(&buf);
            tidyNodeGetText(doc, child, &buf);
            char *text = buf.bp ? (char *)buf.bp : "";
            printf("%*.*s%s", indent, (int)strlen(text), "", text);
            tidyBufFree(&buf);
        }
        dumpNode(doc, child, indent + 4); /* recursive */
        if (name)
        {
            printf("%*.*s%s\n", indent, (int)strlen(name), "", name);
        }
    }
}

int main()
{
    TidyDoc tdoc = tidyCreate();
    int err = tidyParseFile(tdoc, "index.html");
    if (err < 0)
    {
        fprintf(stderr, "%s %d\n", "tidyParseString return", err);
        return -1;
    }
    err = tidyCleanAndRepair(tdoc);
    if (err < 0)
    {
        fprintf(stderr, "%s %d\n", "tidyCleanAndRepair return", err);
        return -1;
    }
    dumpNode(tdoc, tidyGetRoot(tdoc), 0);
    tidyRelease(tdoc);
}