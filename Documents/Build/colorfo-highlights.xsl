<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:d="http://docbook.org/ns/docbook" xmlns:xslthl="http://xslthl.sf.net"
    exclude-result-prefixes="xslthl d" version="1.0">

    <xsl:import href="common-highlights.xsl"/>

    <xsl:template match="xslthl:keyword" mode="xslthl">
        <xsl:apply-templates mode="xslthl"/>
    </xsl:template>

    <xsl:template match="xslthl:basic-type" mode="xslthl">
        <xsl:apply-templates mode="xslthl"/>
    </xsl:template>

    <xsl:template match="xslthl:type-modifier" mode="xslthl">
            <xsl:apply-templates mode="xslthl"/>
    </xsl:template>

    <xsl:template match="xslthl:sampler-type" mode="xslthl">
            <xsl:apply-templates mode="xslthl"/>
    </xsl:template>
    
    <xsl:template match="xslthl:library-func" mode="xslthl">
            <xsl:apply-templates mode="xslthl"/>
    </xsl:template>
    
    <xsl:template match="xslthl:string" mode="xslthl">
            <xsl:apply-templates mode="xslthl"/>
    </xsl:template>

    <xsl:template match="xslthl:comment" mode="xslthl">
            <xsl:apply-templates mode="xslthl"/>
    </xsl:template>

    <xsl:template match="xslthl:directive" mode="xslthl">
            <xsl:apply-templates mode="xslthl"/>
    </xsl:template>

    <xsl:template match="xslthl:tag" mode="xslthl">
            <xsl:apply-templates mode="xslthl"/>
    </xsl:template>

    <xsl:template match="xslthl:attribute" mode="xslthl">
            <xsl:apply-templates mode="xslthl"/>
    </xsl:template>

    <xsl:template match="xslthl:value" mode="xslthl">
            <xsl:apply-templates mode="xslthl"/>
    </xsl:template>

    <xsl:template match="xslthl:html" mode="xslthl">
            <xsl:apply-templates mode="xslthl"/>
    </xsl:template>

    <xsl:template match="xslthl:xslt" mode="xslthl">
            <xsl:apply-templates mode="xslthl"/>
    </xsl:template>

    <xsl:template match="xslthl:number" mode="xslthl">
            <xsl:apply-templates mode="xslthl"/>
    </xsl:template>

    <xsl:template match="xslthl:annotation" mode="xslthl">
            <xsl:apply-templates mode="xslthl"/>
    </xsl:template>

    <!-- Not sure which element will be in final XSLTHL 2.0 -->
    <xsl:template match="xslthl:doccomment|xslthl:doctype" mode="xslthl">
            <xsl:apply-templates mode="xslthl"/>
    </xsl:template>

</xsl:stylesheet>
