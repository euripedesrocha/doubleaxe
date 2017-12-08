<?xml version='1.0' encoding="UTF-8"?>
<!--
Implementation by the Keccak, Keyak and Ketje Teams, namely, Guido Bertoni,
Joan Daemen, Michaël Peeters, Gilles Van Assche and Ronny Van Keer, hereby
denoted as "the implementer".

For more information, feedback or questions, please refer to our websites:
http://keccak.noekeon.org/
http://keyak.noekeon.org/
http://ketje.noekeon.org/

To the extent possible under law, the implementer has waived all copyright
and related or neighboring rights to the source code in this file.
http://creativecommons.org/publicdomain/zero/1.0/
-->
<xsl:stylesheet
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    version='1.0'>

<xsl:output method="text" indent="no" encoding="UTF-8"/>

<xsl:template match="target">
    <xsl:variable name="targetfile" select="concat('bin/.build/', @name, '.target')"/>
    <xsl:variable name="makefile" select="concat('bin/.build/', @name, '.make')"/>
    <xsl:variable name="object" select="concat('bin/', @name)"/>
    <xsl:variable name="pack" select="concat(@name, '.pack')"/>
    <xsl:variable name="all" select="../@all"/>

    <xsl:if test="$all!=''">
        <xsl:value-of select="$all"/>
        <xsl:text>: </xsl:text>
        <xsl:value-of select="@name"/>
        <xsl:text>
</xsl:text>
        <xsl:value-of select="$all"/>
        <xsl:text>.packs: </xsl:text>
        <xsl:value-of select="$pack"/>
        <xsl:text>
</xsl:text>
    </xsl:if>

    <xsl:text>.PHONY: </xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text> </xsl:text>
    <xsl:value-of select="$object"/>
    <xsl:text> </xsl:text>
    <xsl:value-of select="$pack"/>
    <xsl:text>
</xsl:text>

    <xsl:value-of select="@name"/>
    <xsl:text>: </xsl:text>
    <xsl:value-of select="$object"/>
    <xsl:text>
</xsl:text>

    <xsl:value-of select="$object"/>
    <xsl:text>: </xsl:text>
    <xsl:value-of select="$makefile"/>
    <xsl:text>
&#9;$(MAKE) -f </xsl:text>
    <xsl:value-of select="$makefile"/>
    <xsl:text> </xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>
</xsl:text>

    <xsl:value-of select="$pack"/>
    <xsl:text>: </xsl:text>
    <xsl:value-of select="$makefile"/>
    <xsl:text>
&#9;$(MAKE) -f </xsl:text>
    <xsl:value-of select="$makefile"/>
    <xsl:text> </xsl:text>
    <xsl:value-of select="$pack"/>
    <xsl:text>
</xsl:text>

    <xsl:value-of select="$makefile"/>
    <xsl:text>: </xsl:text>
    <xsl:value-of select="$targetfile"/>
    <xsl:text> Build/ToTargetMakefile.xsl
&#9;xsltproc -o $@ Build/ToTargetMakefile.xsl $&lt;
</xsl:text>

    <xsl:value-of select="$targetfile"/>
    <xsl:text>: Build/ToOneTarget.xsl bin/.build/Makefile.expanded Makefile.build
&#9;xsltproc -o $@ -param nameTarget "'</xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>'" Build/ToOneTarget.xsl bin/.build/Makefile.expanded

</xsl:text>
</xsl:template>

<xsl:template match="group">
    <xsl:if test="@all!=''">
        <xsl:text>.PHONY: </xsl:text>
        <xsl:value-of select="@all"/>
        <xsl:text> </xsl:text>
        <xsl:value-of select="@all"/><xsl:text>.packs</xsl:text>
        <xsl:text>
</xsl:text>
        <xsl:if test="../@all!=''">
            <xsl:value-of select="../@all"/>
            <xsl:text>: </xsl:text>
            <xsl:value-of select="@all"/>
            <xsl:text>
</xsl:text>
            <xsl:value-of select="../@all"/><xsl:text>.packs</xsl:text>
            <xsl:text>: </xsl:text>
            <xsl:value-of select="@all"/><xsl:text>.packs</xsl:text>
            <xsl:text>
</xsl:text>
        </xsl:if>
    </xsl:if>

    <xsl:apply-templates select="target|group"/>
</xsl:template>

<xsl:template match="group" mode="list">
    <xsl:if test="@all!=''">
        <xsl:text>&#9;@echo "+ </xsl:text>
        <xsl:value-of select="@all"/>
        <xsl:text>[.packs]"
</xsl:text>
    </xsl:if>
    <xsl:apply-templates select="target|group" mode="list"/>
</xsl:template>

<xsl:template match="target" mode="list">
    <xsl:text>&#9;@echo "- </xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>[.pack]"
</xsl:text>
</xsl:template>

<xsl:template match="build">
<xsl:text>.PHONY: _list
_list:
&#9;@echo "The defined targets (-) and groups of targets (+) are:"
</xsl:text>
    <xsl:if test="@all!=''">
        <xsl:text>&#9;@echo "+ </xsl:text>
        <xsl:value-of select="@all"/>
        <xsl:text>[.packs]"
</xsl:text>
    </xsl:if>
    <xsl:apply-templates select="target|group" mode="list"/>
        <xsl:text>
</xsl:text>

    <xsl:if test="@all!=''">
        <xsl:text>.PHONY: </xsl:text>
        <xsl:value-of select="@all"/>
        <xsl:text> </xsl:text>
        <xsl:value-of select="@all"/><xsl:text>.packs</xsl:text>
        <xsl:text>
</xsl:text>
    </xsl:if>

    <xsl:apply-templates select="target|group"/>
</xsl:template>

</xsl:stylesheet>
